/*
 * @Author: Zazu
 * @Date:   2019-01-26 15:10:14
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 18:22:54
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fileType.h>

const char illegalChars[] = {';','|','&'};

static char* getFileType(char* filename){
   char* command = (char*)malloc(sizeof(char)*100);
   char* response = (char*)malloc(sizeof(char)*100);

   sprintf(command, "file -b -i %s", filename);
   FILE* pFile = NULL;
   pFile = popen(command, "r");

   fgets(response, 100, pFile);
   pclose(pFile);
   free(command);

   return response;

}

static IMAGE_TYPE getImageType(char* filetype){
   IMAGE_TYPE type = NOT_AN_IMAGE;

   char* temp = NULL;

   if(strncmp(filetype, "image/", 6) == 0){
      temp = filetype + 6;

      if(strncmp(temp, "jpeg", 4) == 0)
         type = JPG;
      else if(strncmp(temp, "png", 3) == 0)
         type = PNG;
      else
         type = UNKNOWN_FORMAT;
   }

   return type;
}

IMAGE_TYPE detectImageType(char* filename){

   char* filetype = getFileType(filename);
   IMAGE_TYPE imageType = getImageType(filetype);
   free(filetype);
   return imageType;
}