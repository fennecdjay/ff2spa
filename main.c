#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <soundpipe.h>

struct Spa
{
  char magic;
  char nchan;
  uint16_t sr;
  uint32_t len;
};

int main()
{
  int i, j;
  uint8_t hdr[strlen("farbfeld") + 2 * sizeof(uint32_t)];
  uint16_t h, w, rgba[4];
  SPFLOAT *d;

  fread(hdr, sizeof(hdr), 1, stdin);
  w = ntohl(*((uint32_t *)(hdr + 8)));
  h = ntohl(*((uint32_t *)(hdr + 12)));
  d = calloc(w, sizeof(SPFLOAT));
  if(!(h%2))
    h--;
  for(i = 0; i < h; i++) {
    for(j = 0; j < w; j++)  {
      fread(rgba, sizeof(uint16_t), 4, stdin);
      if(!rgba[0] & 0xff)
        d[j] = ((SPFLOAT)(h-i)/(h-1.0) - 1) *2;
    }
  }
  struct Spa spa = { 100, 1, w, 48000 };
  fwrite(&spa, sizeof(spa), 1, stdout);
  for(i = 0; i < w; i++)
    fwrite(d, sizeof(SPFLOAT), w, stdout);
  free(d);
  return 0;
}
