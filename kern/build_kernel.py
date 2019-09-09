from common import *
import os
import glob
import log
import subprocess

current_dir = os.environ['PWD']
source_dirs = ['kern/src']

def run(props):
    def loop(dirs, logLevel = 1):
        from os.path import join, exists, split
        
        for dir in dirs:
            path = join(current_dir, dir)
            
            if not exists(path):
                log.warn(f'Unknown directory “{path}”!', logLevel)
                return
            
            directories, files = getDirsAndFiles(path)
            
            loop(directories, logLevel + 1)
            
            for pattern in ['*.c', '*.s']:
                for file in glob.glob(join(path, pattern), recursive=False):
                    log.info('Compiling file “{}”...'.format(file), logLevel)
                    path2, filename = split(file)
                    command = [CC, file, '-o', join(path2, filename.replace(pattern.replace('*', ''), '.o'))] + CC_FLAGS + ['-Ikern/include', '-Istd/include']
                    if props['debug']:
                        log.debug('Command used: {}'.format(' '.join(command)), logLevel)
                    cmd = subprocess.Popen(command, stdout=subprocess.PIPE)
                    cmd.wait()
                    if cmd.returncode != 0:
                        log.error('Subcommand returned with a non-0 exit code.', logLevel)
                        exit(cmd.returncode)
    loop(source_dirs)