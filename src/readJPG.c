/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:36
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:36
*/


#include <stdio.h>
#include <jpeglib.h>

#include <readJPG.h>

Image* readJPG(char* filename){
   struct jpeg_decompress_struct cinfo;

   struct jpeg_error_mgr jerr;
   FILE* infile;
   JSAMPARRAY buffer;
   int row_stride, width, height, ii = 0;

   Image* image = NULL;

   infile = fopen(filename, "rb");

   if(infile == NULL)
      return NULL;

   cinfo.err = jpeg_std_error(&jerr);

   jpeg_create_decompress(&cinfo);

   jpeg_stdio_src(&cinfo, infile);

   jpeg_read_header(&cinfo, TRUE);

   jpeg_start_decompress(&cinfo);

   width = cinfo.output_width;
   height = cinfo.output_height;

   image = createImage(width, height);

   row_stride = cinfo.output_width * cinfo.output_components;

   buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


   while(cinfo.output_scanline < cinfo.output_height){
      jpeg_read_scanlines(&cinfo, buffer, 1);

      image->pixels[ii]->rgb[PIXEL_RED] = buffer[0][0];
      image->pixels[ii]->rgb[PIXEL_GREEN] = buffer[0][1];
      image->pixels[ii]->rgb[PIXEL_BLUE] = buffer[0][2];

      ii++;

   }

   printf("%d * %d : %d\n", width, height, cinfo.output_components);

   jpeg_destroy_decompress(&cinfo);

   fclose(infile);

   return image;

}

void saveJPG(Image* image, char* filename){

}