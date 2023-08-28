#ifndef ERROR_H
#define ERROR_H

#define ASSERT_MF(B, M, ...)                                                         \
    do {                                                                             \
        if (!(B)) {                                                                  \
            fprintf(stderr, (M), __VA_ARGS__);                                       \
            fprintf(stderr, " (%s, %d)\n", __func__, __LINE__);                      \
            exit(1);                                                                 \
        }                                                                            \
    } while (0)

#define ASSERT_M(B, M) ASSERT_MF(B, M, NULL)

#endif
