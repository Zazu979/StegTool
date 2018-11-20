#ifndef COMPRESSION_H
#define COMPRESSION_H

uint32_t getFileLength(char* filename);
void compressFile(char* infilename, char* outfilename);
void decompressFile(char* infilename, char* outfilename);

#define COMPRESSED_FILE "/tmp/stegCompress"
#define DECOMPRESSED_FILE "/tmp/stegDecompress"

#endif
