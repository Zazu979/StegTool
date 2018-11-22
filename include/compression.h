/*
* @Author: zazu
* @Date:   2018-11-21 00:20:10
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-22 10:42:23
*/

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

uint32_t getFileLength(char* filename);
void compressFile(char* infilename, char* outfilename);
void decompressFile(char* infilename, char* outfilename);

#define COMPRESSED_FILE "/tmp/stegCompress"
#define DECOMPRESSED_FILE "/tmp/stegDecompress"

#endif
