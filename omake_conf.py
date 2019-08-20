#!python3

import os, subprocess, log, re
import glob

## Constants

CC = 'i386-elf-gcc'
CC_FLAGS = ['-Wall', '-Wextra', '-m32', '-fno-builtin', '-ffreestanding', '-nostdlib'
           , '-fno-leading-underscore', '-g', '-Ic/include', '-c', '-fno-stack-protector'
           , '-lgcc']

AS = CC # 'i386-elf-as'
AS_FLAGS = CC_FLAGS # ['--32']

LD = CC
LD_FLAGS = list(filter(lambda p: p != '-c', CC_FLAGS))

binaries = ['*.o', '*.bin']
current_dir = os.environ['PWD']
sourceDirs = ['asm', 'bin', 'c']
binName = 'oneiric.bin'
imageDir = 'bin'
imageName = 'oneiric.img'

###########################################################################################################################################
## Config actions

def clean(props):
    def clean2(dirs, logLevel=1):
        from os.path import join, exists
        
        for dir in dirs:
            path = join(current_dir, dir)
            log.info(f'Cleaning directory “{path}”...', logLevel)
            
            if not exists(path):
                log.warn(f'Unknown directory “{path}”!', logLevel)
                return
            
            directories, files = _getDirsAndFiles(path)
            
            clean2(directories, logLevel + 1)
            
            for pattern in binaries:
                for file in glob.glob(join(path, pattern), recursive=False):
                    if props['debug']:
                        log.debug('Removing file “{}”.'.format(join(path, file)), logLevel)
                    os.remove(join(path, file))
    clean2(sourceDirs)
    
def build_c(props):
    def build_c2(dirs, logLevel=1):
        from os.path import join, exists, split
        
        for dir in dirs:
            path = join(current_dir, dir)
            
            if not exists(path):
                log.warn(f'Unknown directory “{path}”!', logLevel)
                return
            
            directories, files = _getDirsAndFiles(path)
            
            build_c2(directories, logLevel + 1)
            
            for file in glob.glob(join(path, '*.c'), recursive=False):
                log.info('Compiling file “{}”...'.format(file), logLevel)
                path2, filename = split(file)
                command = [CC] + CC_FLAGS + ['-o', join(path2, filename.replace('.c', '.o'))] + [file]
                if props['debug']:
                    log.debug('Command used: {}'.format(' '.join(command)), logLevel)
                cmd = subprocess.Popen(command, stdout=subprocess.PIPE)
                cmd.wait()
                if cmd.returncode != 0:
                    log.error('Subcommand returned with a non-0 exit code.', logLevel)
                    exit(cmd.returncode)
    build_c2(sourceDirs)
    
def build_asm(props):
    def build_asm2(dirs, logLevel=1):
        from os.path import join, exists, split
        
        for dir in dirs:
            path = join(current_dir, dir)
            
            if not exists(path):
                log.warn(f'Unknown directory “{path}”!', logLevel)
                return
            
            directories, files = _getDirsAndFiles(path)
            
            build_asm2(directories, logLevel + 1)
            
            for file in glob.glob(join(path, '*.s'), recursive=False):
                log.info('Compiling file “{}”...'.format(file), logLevel)
                path2, filename = split(file)
                command = [AS] + AS_FLAGS + ['-o', join(path2, filename.replace('.s', '.o'))] + [file]
                if props['debug']:
                    log.debug('Command used: {}'.format(' '.join(command)), logLevel)
                cmd = subprocess.Popen(command, stdout=subprocess.PIPE)
                cmd.wait()
                if cmd.returncode != 0:
                    log.error('Subcommand returned with a non-0 exit code.', logLevel)
                    exit(cmd.returncode)
    build_asm2(sourceDirs)
    
def build_bin(props):
    import itertools
    
    log.info('Linking binary...', 1)
    
    def get_o(dir, logLevel=0):
        if not os.path.exists(dir):
            log.warn(f'Unknown directory “{dir}”!', logLevel)
            return
        
        directories, files = _getDirsAndFiles(dir)
        f = glob.glob(os.path.join(dir, '*.o'), recursive=False)
        return f + list(itertools.chain.from_iterable(map(lambda f: get_o(f, logLevel + 1), directories)))
    
    o_files = list(map(get_o, list(map(lambda p: os.path.join(current_dir, p), sourceDirs))))
    flattened = list(itertools.chain.from_iterable(o_files))
    
    command = [LD] + ['-o', os.path.join(imageDir, binName), '-Wl,-Tlink.ld'] + flattened + LD_FLAGS
    if props['debug']:
        log.debug('Command used: {}'.format(' '.join(command)), 1)
    cmd = subprocess.Popen(command, stdout=subprocess.PIPE)
    cmd.wait()
    if cmd.returncode != 0:
        log.error('Subcommand returned with a non-0 exit code', 1)
        exit(cmd.returncode)
    
###########################################################################################################################################
## Supposedly module private functions
    
def _getDirsAndFiles(path):
    from os.path import isfile, isdir, join
    
    content = os.listdir(path)
    directories = [join(path, d) for d in content if isdir(join(path, d))]
    files = [f for f in content if isfile(join(path, f))]
    return (directories, files)
