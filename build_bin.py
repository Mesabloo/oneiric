from common import *
import os, log, glob, subprocess

binName = 'oneiric.bin'
imageDir = 'bin'
imageName = 'oneiric.img'
sourceDirs = ['kern', 'std']

def run(props):
    import itertools
    
    log.info('Linking binary...', 1)
    current_dir = os.environ['PWD']
    
    def get_o(dir, logLevel=0):
        if not os.path.exists(dir):
            log.warn(f'Unknown directory “{dir}”!', logLevel)
            return
        
        directories, files = getDirsAndFiles(dir)
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