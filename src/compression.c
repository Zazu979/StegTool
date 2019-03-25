/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:49:44
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-03-08 17:14:20
*/
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

#include <compression.h>

uint32_t getFileLength(char* filename){
   FILE* file = fopen(filename, "rb");
   uint32_t length = 0;

   if(file != NULL){
      fseek(file, 0, SEEK_END);       
      length = ftell(file);          

      fclose(file);

      if(length > UINT_MAX){
         printf("Text file is to large to be used. Sorry :(\n");
         length = 0;
      }
   }else{
      printf("Invalid Text file\n");
   }

   return length;
   
}

void decompressFile(char *infilename, char *outfilename)
{
   gzFile infile = gzopen(infilename, "rb");
   FILE *outfile = fopen(outfilename, "wb");
   
   char buffer[128];
   int num_read = 0;
   
   printf("Decompression time\n");
   
   if (!infile || !outfile) 
      return;

   while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
      fwrite(buffer, 1, num_read, outfile);
   }

   gzclose(infile);
   fclose(outfile);
}

char* compressFile(char *infilename, char *outfilename)
{
   FILE *infile = fopen(infilename, "rb");
   gzFile outfile = gzopen(outfilename, "wb");

   char inbuffer[128];
   int num_read = 0;
   unsigned long total_read = 0;
   
   if (!infile || !outfile) 
      return NULL;
   
   while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
      total_read += num_read;
      gzwrite(outfile, inbuffer, num_read);
   }
   
   fclose(infile);
   gzclose(outfile);
   
   if(total_read < getFileLength(outfilename)){
      printf("Using the original file\n");
      return infilename;
   }else{
      printf("Using the compressed file\n");
      return outfilename;
   }

   printf("Read %ld bytes, Wrote %d bytes,Compression factor %4.2f%%\n",
      total_read, getFileLength(outfilename),
      (1.0-getFileLength(outfilename)*1.0/total_read)*100.0);
}