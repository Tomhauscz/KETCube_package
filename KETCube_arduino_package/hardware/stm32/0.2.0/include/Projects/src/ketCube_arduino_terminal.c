/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ketCube_cfg.h"
#include "ketCube_terminal.h"
#include "ketCube_arduino.h"
#include "ketCube_arduino_terminal.h"

void ketCube_terminal_print(char* str)
{
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ARDUINO, str);
}

void ketCube_terminal_printf(char* formatted_string, ...)
{
    char str[100];
    
    va_list args;
    va_start(args, formatted_string);
    vsprintf(str, formatted_string, args);
    va_end(args);
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ARDUINO, str);
}

void ketCube_terminal_printInt(char* formatted_string, int int_number)
{
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ARDUINO, formatted_string, int_number);
}