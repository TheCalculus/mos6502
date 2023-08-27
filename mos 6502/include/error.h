#ifndef ERROR_H
#define ERROR_H

#ifndef ASSERT_M

#ifdef __func__

#define ASSERT_FUNCTION_NAME __func__

#elif defined(__FUNCTION__)

#define ASSERT_FUNCTION_NAME __FUNCTION__

#else

#define ASSERT_FUNCTION_NAME "UnknownFunction"

#endif

#define ASSERT_M(B, M)                                                             \
    do {                                                                           \
        if (!(B)) {                                                                \
            fprintf(stderr, "%s (%s, %d)\n", (M), ASSERT_FUNCTION_NAME, __LINE__); \
            exit(1);                                                               \
        }                                                                          \
    } while (0)

#endif

#endif
