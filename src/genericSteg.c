/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:51
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 15:19:08
*/

#include <stdio.h>

#include <genericSteg.h>

/** The possible combinations that can the RGB values can be ordered.
 *  Used to add a level of un structure to make it harder to extract the
 *  information from the image without this tool.
 */
const int RGB_ORDERS[6][3] = {
   {0,1,2},
   {0,2,1},
   {1,0,2},
   {1,2,0},
   {2,0,1},
   {2,1,0} 
};

const int* getOrder(Pixel* pixel){
   if(pixel == NULL){
      return RGB_ORDERS[0];
   }else{
      int sum = 0;
      sum += pixel->rgb[0];
      sum += pixel->rgb[1];
      sum += pixel->rgb[2];

      return RGB_ORDERS[sum % 6];
   }
}