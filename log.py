def info(message, level):
    print('\033[32m{}\033[0m'.format(_createMessage(message, level, '[i]')))
    
def debug(message, level):
    print('\033[34m{}\033[0m'.format(_createMessage(message, level, '...')))
    
def warn(message, level):
    print('\033[33m{}\033[0m'.format(_createMessage(message, level, '/!\\')))
                           
def error(message, level):
    print('\033[31m{}\033[0m'.format(_createMessage(message, level, '(!)')))
    
def _createMessage(msg, lvl, prefix):
    messages = map(lambda m: '{} {}> {}'.format(prefix, '| ' * lvl, m), msg.split('\n'))
    return '\n'.join(messages)
