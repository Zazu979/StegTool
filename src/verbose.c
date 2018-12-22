/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:52:05
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:52:05
*/


#include <verbose.h>

bool verbose = false;

void setVerbose(bool setting){
   verbose = setting;
}

void vprint(const char* format, ...){
   if(verbose){
      va_list args;
      va_start(args, format);

      vprintf(format, args);

      va_end(args);
   }
}
