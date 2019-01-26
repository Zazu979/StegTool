/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:49:36
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2019-01-26 15:10:48
*/
#include <stdio.h> 

#include <stdint.h>
#include <binary.h>

int binToVal(int binValue[8]){
   int ii, val = 0;

   for (ii = 0; ii < 8; ii++ ){
      val *= 2;
      val += binValue[ii];   
   }

   return val;

}

void charToBin(unsigned char value,int binValue[8]){
   for(int ii = 7; ii >= 0; ii--){
      binValue[ii] = value & 1;
      value >>= 1;
   }
}

// void uint32ToBin(uint32_t value, int binValue[32]){
//    int ii, temp;

//    for (ii = 0; ii < 32; ++ii){
//       temp = value >> ii;
//       binValue[31-ii] = temp&1;
//    }
// }