/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:48:58
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 11:52:51
*/
 

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

uint32_t getFileLength(char* filename);
char* compressFile(char* infilename, char* outfilename);
void decompressFile(char* infilename, char* outfilename);

#define COMPRESSED_FILE "/tmp/stegCompress"
#define DECOMPRESSED_FILE "/tmp/stegDecompress"

#endif
