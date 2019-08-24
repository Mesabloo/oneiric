#pragma once
#ifndef LOGS_H
#define LOGS_H

void info(char const* first, ...);
void warn(char const* first, ...);
void error(char const* first, ...);
void ok(char const* first, ...);
void failed(char const* first, ...);

#endif