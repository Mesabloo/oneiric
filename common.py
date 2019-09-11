## Constants

CC = 'i386-elf-gcc'
CC_FLAGS = ['-Wall', '-Wextra', '-m32', '-fno-builtin', '-ffreestanding', '-nostdlib'
           , '-fno-leading-underscore', '-g3', '-c', '-fno-stack-protector'
           , '-lgcc'] #, '-DENABLE_LOGGING']

AS = CC # 'i386-elf-as'
AS_FLAGS = CC_FLAGS # ['--32']

LD = CC
LD_FLAGS = [p for p in CC_FLAGS if p != '-c']

binaries = ['*.o', '*.bin']

########################################################################################################

def getDirsAndFiles(path):
    from os.path import isfile, isdir, join
    import os
    
    content = os.listdir(path)
    directories = [join(path, d) for d in content if isdir(join(path, d))]
    files = [f for f in content if isfile(join(path, f))]
    return (directories, files)