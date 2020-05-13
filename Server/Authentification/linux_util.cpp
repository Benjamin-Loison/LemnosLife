#include "linux_bcrypt.h"
#ifdef __cplusplus
extern "C" {
#endif
void explicit_bzero(void *b, size_t len)
{
	(*explicit_memset)(b, 0, len);
}
#ifdef __cplusplus
}
#endif
