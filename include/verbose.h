/*
* @Author: zazu
* @Date:   2018-11-21 23:22:37
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 23:46:59
*/
#ifndef VERBOSE_H
#define VERBOSE_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

void setVerbose(bool verbose);
void vprint(const char* format, ...);
#endif