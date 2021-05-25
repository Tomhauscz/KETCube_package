/* 
 * File:   ketCube_arduino_terminal.h
 * Author: Tomáš Hák
 *
 * Created on 24. září 2019, 19:51
 */

#ifndef KETCUBE_ARDUINO_TERMINAL_H
#define KETCUBE_ARDUINO_TERMINAL_H

#include <stdarg.h>
#include "ketCube_terminal.h"

static inline void ketCube_printfInfo(char* formated_string, ...)
{
    va_list args;
    va_start(args, formated_string);
    ketCube_terminal_ModSeverityPrintln(KETCUBE_CFG_SEVERITY_INFO, KETCUBE_LISTS_MODULEID_ARDUINO, formated_string, args);
    va_end(args);
}

static inline void ketCube_printfError(char* formated_string, ...)
{
    va_list args;
    va_start(args, formated_string);
    ketCube_terminal_ModSeverityPrintln(KETCUBE_CFG_SEVERITY_ERROR, KETCUBE_LISTS_MODULEID_ARDUINO, formated_string, args);
    va_end(args);
}

static inline void ketCube_printfWarning(char* formated_string, ...)
{
    va_list args;
    va_start(args, formated_string);
    ketCube_terminal_ModSeverityPrintln(KETCUBE_CFG_SEVERITY_DEBUG, KETCUBE_LISTS_MODULEID_ARDUINO, formated_string, args);
    va_end(args);
}

static inline void ketCube_printfNone(char* formated_string, ...)
{
    va_list args;
    va_start(args, formated_string);
    ketCube_terminal_ModSeverityPrintln(KETCUBE_CFG_SEVERITY_NONE, KETCUBE_LISTS_MODULEID_ARDUINO, formated_string, args);
    va_end(args);
}

#endif /* KETCUBE_ARDUINO_TERMINAL_H */

