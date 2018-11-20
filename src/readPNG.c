/*
* @Author: zazu
* @Date:   2018-11-20 18:06:08
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-20 22:37:48
*/

#include <png.h>
#include <image.h>
#include <readPNG.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct{
   png_bytep* rows;

   /*3 for RGB, 4 for RGBA*/
   int pixelValues;

   int width;
   int height;
}PNGImage;

static Image* convertToImage(PNGImage* pngImage);
static PNGImage* readPNGFile(char* filename);
static void freePNG(PNGImage* pngImage);

Image* readPNG(char* filename){
   
   PNGImage* pngImage = readPNGFile(filename);

   Image* image = convertToImage(pngImage);

   freePNG(pngImage);

   return image;
}

static void freePNG(PNGImage* image){
   int ii;

   for(ii = 0; ii < image->height; ii++)
      free(image->rows[ii]);
   free(image->rows);

   free(image);
}

static Image* convertToImage(PNGImage* pngImage){

   int ii = 0, jj = 0;
   int width = pngImage->width;
   int height = pngImage->height;

   png_byte* row,* ptr;

   Image* image = createImage(width, height);

   Pixel* pixel;

   for(ii = 0; ii < height; ii++){
      row = pngImage->rows[ii];
      for(jj = 0; jj < width; jj++){
         ptr = &(row[jj*pngImage->pixelValues]);
         pixel = &(image->pixels[ii][jj]);

         pixel->rgb[0] = ptr[0];
         pixel->rgb[1] = ptr[1];
         pixel->rgb[2] = ptr[2];

      }
   }

   return image;
}

static PNGImage* readPNGFile(char* filename){
   PNGImage* image = (PNGImage*)malloc(sizeof(PNGImage));
   png_structp pngPtr;
   png_infop infoPtr;

   /*Unsigned removes compiler errors*/
   unsigned char header[8];

   int ii = 0;

   FILE* file = fopen(filename, "rb");

   if(file == NULL){
      printf("File %s could not be opened for reading\n", filename);
      return NULL;
   }

   fread(header, 1, 8, file);

   if(png_sig_cmp(header, 0, 8)){
      printf("File %s is not recognised as a PNG file\n", filename);
      return NULL;
   }

   /*Initialising stuff*/
   pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   infoPtr = png_create_info_struct(pngPtr);

   png_init_io(pngPtr, file);
   png_set_sig_bytes(pngPtr,8);

   png_read_info(pngPtr, infoPtr);

   image->width = png_get_image_width(pngPtr, infoPtr);
   image->height = png_get_image_height(pngPtr, infoPtr);

   image->rows = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
   for (ii=0; ii<image->height; ii++){
      image->rows[ii] = (png_byte*)malloc(png_get_rowbytes(pngPtr, infoPtr));
   }

   /*Read image into the image->rows*/
   png_read_image(pngPtr, image->rows);

   switch(png_get_color_type(pngPtr, infoPtr)){
      case PNG_COLOR_TYPE_RGBA:
         image->pixelValues = 4;
         break;
      case PNG_COLOR_TYPE_RGB: default:
         image->pixelValues = 3;
         break;
   }

   fclose(file);
   png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

   return image;
}