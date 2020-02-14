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

#if __SIZEOF_POINTER__ == 8
#define Elf_Dyn Elf64_Dyn
#else
#define Elf_Dyn Elf32_Dyn
#endif

extern unsigned long _DYNAMIC;

static void ctors(void);
static void dtors(void);

extern EFI_STATUS _relocate(unsigned long ldbase, Elf64_Dyn *dyn,
			    EFI_HANDLE image, EFI_SYSTEM_TABLE *systab);

EFI_STATUS
_start(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
	EFI_STATUS status;
	unsigned long ldbase;
	EFI_LOADED_IMAGE *loaded_image;
	Elf_Dyn *dyn;
	EFI_GUID loaded_image_protocol = EFI_LOADED_IMAGE_PROTOCOL_GUID;

	systab->BootServices->HandleProtocol(image, &loaded_image_protocol,
					     (void *)&loaded_image);

	ldbase = (unsigned long)loaded_image->ImageBase;

	dyn = (void *)((unsigned long)&_DYNAMIC + ldbase);

	status = _relocate(ldbase, dyn, image, systab);
	if (EFI_ERROR(status))
		return status;

	InitializeLib(image, systab);
	ctors();
	status = efi_main(image, systab);
	dtors();

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

static void ctors(void)
{
	for (funcp *location = (void *)&_init_array; location < (funcp *)&_init_array_end; location++) {
		funcp func = *location;
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

static void dtors(void)
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

// vim:fenc=utf-8:tw=75:noet
