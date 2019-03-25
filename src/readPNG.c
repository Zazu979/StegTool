/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:52:02
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 20:59:06
*/


#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include <readPNG.h>

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

void savePNG(Image* image, char* filename){

   FILE* file = NULL;
   png_structp png_ptr = NULL;
   png_infop info_ptr = NULL;
   png_bytep row = NULL;
   Pixel* pixel = NULL;

   int ii,jj, kk;
   char title[] = "This has been Stegged";

   int width = image->width;
   int height = image->height;

   //TODO fix error handling to be uniform

   printf("Save PNG\n");

   /*Open file for writing (binary mode)*/
   file = fopen(filename, "wb");
   if (file == NULL) {
      fprintf(stderr, "Could not open file %s for writing\n", filename);
   }

   /*Initialize write structure*/
   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (png_ptr == NULL) {
      fprintf(stderr, "Could not allocate write struct\n");
   }

   /*Initialize info structure*/
   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL) {
      fprintf(stderr, "Could not allocate info struct\n");
   }

   /*Setup Exception handling*/
   if (setjmp(png_jmpbuf(png_ptr))) {
      fprintf(stderr, "Error during png creation\n");
   }

   png_init_io(png_ptr, file);

   /*Write header (8 bit colour depth)*/
   png_set_IHDR(png_ptr, info_ptr, width, height,
         8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

   /*Set title*/
   if (title != NULL) {
      png_text title_text;
      title_text.compression = PNG_TEXT_COMPRESSION_NONE;
      title_text.key = "Title";
      title_text.text = title;
      png_set_text(png_ptr, info_ptr, &title_text, 1);
   }

   png_write_info(png_ptr, info_ptr);

   /*Allocate memory for one row (3 bytes per pixel - RGB)*/
   row = (png_bytep) malloc(3 * width * sizeof(png_byte));

   for (ii = 0 ; ii < height ; ii++) {
      for (jj=0 ; jj < width ; jj++) {
         pixel = &(image->pixels[ii][jj]);
         for(kk = 0; kk < 3; kk++){  
            row[(jj*3)+kk] = pixel->rgb[kk];
         }
      }
      png_write_row(png_ptr, row);
   }

   png_write_end(png_ptr, NULL);

   /*CLEANUP*/
   fclose(file);
   png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
   png_destroy_write_struct(&png_ptr, &info_ptr);
   free(row);


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

   printf("Read PNG\n");

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