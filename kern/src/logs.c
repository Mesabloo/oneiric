#include <utils/logs.h>
#include <stdarg.h>
#include <std/io/console.h>

void info(char const* first_arg, ...)
{
    va_list args;
    va_start(args, first_arg);

    putsN("\e\x07[\e\x01 INFO \e\x07] ", first_arg, 0);
    vputsN(args);

    va_end(args);
}

void warn(char const* first_arg, ...)
{
    va_list args;
    va_start(args, first_arg);

    putsN("\e\x07[\e\x0E WARN \e\x07] ", first_arg, 0);
    vputsN(args);

    va_end(args);
}

void error(char const* first_arg, ...)
{
    va_list args;
    va_start(args, first_arg);

    putsN("\e\x07[\e\x04ERROR \e\x07] ", first_arg, 0);
    vputsN(args);

    va_end(args);
}

void ok(char const* first_arg, ...)
{
    va_list args;
    va_start(args, first_arg);

    putsN("\e\x07[\e\x0A  OK  \e\x07] ", first_arg, 0);
    vputsN(args);

    va_end(args);
}

void failed(char const* first_arg, ...)
{
    va_list args;
    va_start(args, first_arg);

    putsN("\e\x07[\e\x04", "FAILED\e\x07] ", first_arg, 0);
    vputsN(args);

    va_end(args);
}