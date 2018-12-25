/*
 * @Author: Zazu
 * @Date:   2018-12-22 18:57:16
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 20:37:30
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <openssl/evp.h>
#include <openssl/aes.h>

#include <bool.h>
#include <encryption.h> 

void encrypt(char* infile, char* outfile, unsigned char* key){
   const unsigned BUFSIZE=4096;

   FILE* ifp = fopen(infile, "rb");
   FILE* ofp = fopen(outfile, "wb");

   unsigned char *read_buf = malloc(BUFSIZE);
   unsigned char *cipher_buf;
   unsigned blocksize;
   int out_len;
   EVP_CIPHER_CTX ctx;

   EVP_CipherInit(&ctx, EVP_aes_256_cbc(), key, NULL, TRUE);
   blocksize = EVP_CIPHER_CTX_block_size(&ctx);
   cipher_buf = malloc(BUFSIZE + blocksize);

   while (1) {

      // Read in data in blocks until EOF. Update the ciphering with each read.

      int numRead = fread(read_buf, sizeof(unsigned char), BUFSIZE, ifp);
      EVP_CipherUpdate(&ctx, cipher_buf, &out_len, read_buf, numRead);
      fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
      if (numRead < BUFSIZE) { // EOF
         break;
      }
   }

   // Now cipher the final block and write it out.

   EVP_CipherFinal(&ctx, cipher_buf, &out_len);
   fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);

   // Free memory

   free(cipher_buf);
   free(read_buf);
}