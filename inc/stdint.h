#ifndef PJSTDINT_H
#define PJSTDINT_H

typedef unsigned long uint64_t;
typedef long int64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef signed long intptr_t;

#define SIZE_MAX 0xffffffffffffffffull
#define SSIZE_MAX 0x7fffffffffffffffull
#define UINT32_MAX 0xfffffffful
#define INT32_MAX 0x7ffffffful
#define UINT64_MAX 0xffffffffffffull
#define INT64_MAX 0x7ffffffffffffull

#endif
