// SPDX-License-Identifier: GPL-2-or-later
/*
 * crt0.c
 * Copyright 2020 Peter Jones <pjones@redhat.com>
 *
 */

#include <efi.h>
#include <efilib.h>
#include <elf.h>
#include <stddef.h>

#pragma GCC optimize "-O0"

#define EFI_DEBUG

static const wchar_t hex[] = L"0123456789abcdef";

static void
__attribute__((__unused__))
printval_(EFI_SYSTEM_TABLE *systab, int size, uint64_t value);

static void
__attribute__((__unused__))
print_(EFI_SYSTEM_TABLE *systab, wchar_t *str);

#ifdef EFI_DEBUG
#define printval(a) printval_(systab, sizeof(a), (uint64_t)(a))
#define print(x) print_(systab, (x))
#else
#define printval(a)
#define print(x)
#endif

#if __SIZEOF_POINTER__ == 8
#define Elf_Dyn Elf64_Dyn
#else
#define Elf_Dyn Elf32_Dyn
#endif

extern unsigned long _DYNAMIC;

static void EFIAPI ctors(void);
static void EFIAPI dtors(void);

extern EFI_STATUS _relocate(unsigned long ldbase, Elf64_Dyn *dyn,
			    EFI_HANDLE image, EFI_SYSTEM_TABLE *systab);

EFI_STATUS EFIAPI
_start(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
	EFI_STATUS status;
	unsigned long ldbase;
	EFI_LOADED_IMAGE *loaded_image;
	Elf_Dyn *dyn;
	EFI_GUID loaded_image_protocol = EFI_LOADED_IMAGE_PROTOCOL_GUID;

	print(L"image:"); printval(image);
	print(L"systab:"); printval(systab);
	print(L"systab->BootServices:"); printval(systab->BootServices);
	print(L"systab->BootServices->HandleProtocol:"); printval(systab->BootServices->HandleProtocol);

	systab->BootServices->HandleProtocol(image, &loaded_image_protocol,
					     (void *)&loaded_image);

	print(L"loaded_image:"); printval(loaded_image);
	print(L"loaded_image->ImageBase:"); printval(loaded_image->ImageBase);
	ldbase = (unsigned long)loaded_image->ImageBase;

	print(L"ldbase:"); printval(ldbase);
	print(L"_DYNAMIC:"); printval(_DYNAMIC);
	print(L"&_DYNAMIC:"); printval(&_DYNAMIC);
	dyn = (void *)((unsigned long)&_DYNAMIC + ldbase);
	systab->BootServices->Stall(1000);
	print(L"dyn:"); printval(dyn);
	systab->BootServices->Stall(1000);

	status = _relocate(ldbase, dyn, image, systab);
	systab->BootServices->Stall(1000);
	if (EFI_ERROR(status))
		return status;

	systab->BootServices->Stall(1000);
	InitializeLib(image, systab);
	systab->BootServices->Stall(1000);
	ctors();
	systab->BootServices->Stall(1000);
	status = efi_main(image, systab);
	systab->BootServices->Stall(1000);
	dtors();
	systab->BootServices->Stall(1000);

	return status;
}

/*
 * Note that these aren't the using the GNU "CONSTRUCTOR" output section
 * command, so they don't start with a size.  Because of p2align and the
 * end/END definitions, and the fact that they're mergeable, they can also
 * have NULLs which aren't guaranteed to be at the end.
 */
extern UINTN _init_array, _init_array_end;
extern UINTN __CTOR_LIST__, __CTOR_END__;
extern UINTN _fini_array, _fini_array_end;
extern UINTN __DTOR_LIST__, __DTOR_END__;

typedef void (*funcp)(void);

static void EFIAPI ctors(void)
{
	Print(L"_init_array:%p &_init_array:%p\n", _init_array, &_init_array);
	Print(L"_init_array_end:%p &_init_array_end:%p\n", _init_array_end, &_init_array_end);
	for (funcp *location = (void *)&_init_array; location < (funcp *)&_init_array_end; location++) {
		funcp func = *location;
		Print(L"location:%p *location:%p func:%p\n", location, *location, func);
		if (func != NULL) {
			func();
		}
	}

	for (funcp *location = (void *)&__CTOR_LIST__; location < (funcp *)&__CTOR_END__; location++) {
		funcp func = *location;
		if (func != NULL) {
			func();
		}
	}
}

static void EFIAPI dtors(void)
{
	for (funcp *location = (void *)&__DTOR_LIST__; location < (funcp *)&__DTOR_END__; location++) {
		funcp func = *location;
		if (func != NULL) {
			func();
		}
	}

	for (funcp *location = (void *)&_fini_array; location < (funcp *)&_fini_array_end; location++) {
		funcp func = *location;
		if (func != NULL) {
			func();
		}
	}
}

/*
 * We have to have a some kind of relocations, or else the loader
 * doesn't believe this is position independent, and will try to load
 * us at e.g.  0x1000, which will fail (usually because it's in use).
 *
 * Hand-craft a dummy .reloc section so EFI knows it's a relocatable
 * executable:
 */
struct
	__attribute__((__packed__))
	reloc
{
	uint32_t rva;
	uint32_t block_size;
	uint16_t adj;
};

struct reloc __attribute__((__section__(".reloc"))) dotreloc = {0, 10, 0};

static void
__attribute__((__unused__))
printval_(EFI_SYSTEM_TABLE *systab, int size, uint64_t value)
{
	wchar_t buf[21] = L"0x0000000000000000\r\n";
	int shift;
	uint64_t mask;
	int i;

	switch(size) {
	case 1:
		shift = 4;
		break;
	case 2:
		shift = 12;
		break;
	case 4:
		shift = 28;
		break;
	case 8:
	default:
		shift = 60;
		break;
	}
	mask = 0xfull << shift;

	for (i = 2; mask != 0; i += 2) {
		buf[i] = hex[(value & mask) >> shift];
		mask >>= 4;
		shift -= 4;
		buf[i+1] = hex[(value & mask) >> shift];
		mask >>= 4;
		shift -= 4;
	}
	buf[i+0] = L'\r';
	buf[i+1] = L'\n';
	buf[i+2] = L'\0';

	systab->ConOut->OutputString(systab->ConOut, buf);
}

static void
__attribute__((__unused__))
print_(EFI_SYSTEM_TABLE *systab, wchar_t *str)
{
	systab->ConOut->OutputString(systab->ConOut, str);
}


// vim:fenc=utf-8:tw=75:noet
