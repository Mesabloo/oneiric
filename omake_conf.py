import os, subprocess, log
import glob
from common import *

###########################################################################################################################################
## Config actions

def clean(props):
    sourceDirs = ['kern', 'std', 'bin']
    binaries = ['*.o', '*.bin']
    current_dir = os.environ['PWD']

    def clean2(dirs, logLevel=1):
        from os.path import join, exists
        
        for dir in dirs:
            path = join(current_dir, dir)
            log.info(f'Cleaning directory “{path}”...', logLevel)
            
            if not exists(path):
                log.warn(f'Unknown directory “{path}”!', logLevel)
                return
            
            directories, files = getDirsAndFiles(path)
            
            clean2(directories, logLevel + 1)
            
            for pattern in binaries:
                for file in glob.glob(join(path, pattern), recursive=False):
                    if props['debug']:
                        log.debug('Removing file “{}”.'.format(join(path, file)), logLevel)
                    os.remove(join(path, file))
    clean2(sourceDirs)