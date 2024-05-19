#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <openssl/evp.h>

void create_hash(const char* key, unsigned char* hash)
{
  EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
  const EVP_MD* md = EVP_md5();
  EVP_DigestInit_ex(mdctx, md, NULL);
  EVP_DigestUpdate(mdctx, key, strlen(key));
  EVP_DigestFinal_ex(mdctx, hash, NULL);
  EVP_MD_CTX_free(mdctx);
}

int main()
{
  FILE* input = fopen("input", "r");
  char* key = calloc(16, sizeof(char));
  size_t key_size = 16;
  getline(&key, &key_size, input);

  unsigned char hash[16];

  int num = -1;

  for (int i = 0; num == -1; i++)
    {
      sprintf(key + 8, "%d", i);
      create_hash(key, hash);
      for (int j = 0; hash[j] == 0; j++)
	if (j == 1 && hash[j + 1] < 0x10)
	  {
	    num = i;
	    break;
	  }
    }

  printf("%d\n", num);
  
  return 0;
}
