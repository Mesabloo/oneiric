#!/usr/bin/python3

import argparse, os, log
from inspect import getmembers, isfunction
import importlib.util

args = argparse.ArgumentParser()
args.add_argument('-a', '--action', type=str, action='append', help='The action to execute. Use the same name as a function defined in your configuration file.')
args.add_argument('-c', '--config', type=str, help='Specify the path to a config file.')
args.add_argument('--debug', action='store_const', const=True, help='Choose whether to show the debug output or not', default=False)
args = args.parse_args()

spec = importlib.util.spec_from_file_location('module.name', args.config if args.config else 'omake_conf.py')
config = importlib.util.module_from_spec(spec)
spec.loader.exec_module(config)

config_functions = [fun[0] for fun in getmembers(config, isfunction)]

properties = {'debug' : args.debug}

if not args.action:
    log.error('No action specified...\nExiting now!', 0)
    exit(1)

for act in args.action:
    if len([name for name in config_functions if name == act]) < 1 or not hasattr(config, act):
        log.error('Unknown action “{}” in “{}”.\nPerhaps you forgot to put it into the config file?'.format(act, args.config if args.config else 'omake_conf.py'), 0)
        print('')
        continue
    
    log.info('Executing action “{}” from “{}”'.format(act, args.config if args.config else 'omake_conf.py'), 0)
    getattr(config, act)(properties)
    print('')
