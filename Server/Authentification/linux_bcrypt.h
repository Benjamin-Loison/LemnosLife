#ifdef __linux__

    #include <linux/types.h>
    #include <stdint.h>
    #include <string.h>

    #ifdef __cplusplus
        extern "C" {
    #endif

    #define _PASSWORD_LEN 128
    static void *(*volatile explicit_memset)(void *, int, size_t) = memset;

    #ifdef __cplusplus
        }
    #endif

#endif
