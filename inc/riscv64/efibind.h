/* SPDX-License-Identifier: GPL-2.0+ */

#include <stdint.h>

#define EFIAPI
#define EFI_ERROR_MASK 0x8000000000000000
#define EFIERR(a) (EFI_ERROR_MASK | a)
#define INTERFACE_DECL(x) struct x
#define MIN_ALIGNMENT_SIZE 8
#define RUNTIMEFUNCTION
#define VOID void

typedef uint8_t BOOLEAN;
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef uint16_t WCHAR;

#define BREAKPOINT() while(1);
#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

#define EFI_FUNCTION
