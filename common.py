## Constants

CC = 'i386-elf-gcc'
CC_FLAGS = ['-Wall', '-Wextra', '-m32', '-fno-builtin', '-ffreestanding', '-nostdlib'
           , '-fno-leading-underscore', '-g3', '-c', '-fno-stack-protector'
           , '-lgcc']

AS = CC # 'i386-elf-as'
AS_FLAGS = CC_FLAGS # ['--32']

LD = CC
LD_FLAGS = list(filter(lambda p: p != '-c', CC_FLAGS))

binaries = ['*.o', '*.bin']

########################################################################################################

def getDirsAndFiles(path):
    from os.path import isfile, isdir, join
    import os
    
    content = os.listdir(path)
    directories = [join(path, d) for d in content if isdir(join(path, d))]
    files = [f for f in content if isfile(join(path, f))]
    return (directories, files)