/*
 * @Author: Zazu
 * @Date:   2019-01-26 15:10:19
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 17:59:50
*/

#ifndef FILETYPE_H
#define FILETYPE_H

typedef enum{PNG, JPG, UNKNOWN_FORMAT, NOT_AN_IMAGE}IMAGE_TYPE;

IMAGE_TYPE detectFileExtension(char* filename);
IMAGE_TYPE detectImageType(char* filename);

#endif /* FILETYPE_H */
