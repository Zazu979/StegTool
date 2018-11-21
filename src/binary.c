/*
* @Author: zazu
* @Date:   2018-11-21 11:34:11
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 11:35:41
*/

#include <stdint.h>
#include <binary.h>

int binToVal(int bin[8]){
   int ii, val = 0;

   for (ii = 0; ii < 8; ii++ ){
      val *= 2;
      val += bin[ii];   
   }

   return val;

}

void valToBin(int value, int bin[8]){
   int ii = 0, temp;
   
   for (ii = 0; ii < 8; ++ii){
      temp = value >> ii;
      bin[7-ii] = temp&1;
   }

}

void uint32ToBin(uint32_t value, int bin[32]){
   int ii, temp;

   for (ii = 0; ii < 32; ++ii){
      temp = value >> ii;
      bin[31-ii] = temp&1;
   }
}