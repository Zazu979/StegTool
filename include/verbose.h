/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:45
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:45
*/


#ifndef VERBOSE_H
#define VERBOSE_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

void setVerbose(bool verbose);
void vprint(const char* format, ...);

#endif

