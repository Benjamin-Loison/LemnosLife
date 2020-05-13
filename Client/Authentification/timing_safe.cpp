#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
  int timingsafe_bcmp(const void *b1, const void *b2, size_t n);
#ifdef __cplusplus
}
#endif

int timingsafe_bcmp(const void *b1, const void *b2, size_t n)
{
      const unsigned char *p1 = (const unsigned char*)b1, *p2 = (const unsigned char*)b2;
      int ret = 0;

      for(; n > 0; n--)
            ret |= *p1++ ^ *p2++;
      return ret != 0;
}
