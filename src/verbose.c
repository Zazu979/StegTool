/*
* @Author: zazu
* @Date:   2018-11-21 22:25:45
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 23:50:21
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
