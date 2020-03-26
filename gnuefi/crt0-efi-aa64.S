/*
 * crt0-efi-aa64.S - PE/COFF header for AArch64 EFI applications
 *
 * Copright (C) 2014 Linaro Ltd. <ard.biesheuvel@linaro.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

#include <dwarf.h>

	.arch armv8-a
	.loc_mark_labels 1
	.file 1 __FILE__
	.loc 1 __LINE__ 1 view -0

	.text
.Ltext:
	.align		4

	.globl _start
_start:
#if 0
	stp		x29, x30, [sp, #-32]!
	mov		x29, sp

	str		x0, [sp, #24]
	str		x1, [sp, #16]
	.loc 1 __LINE__ 1 prologue_end

	adrp		x0, ImageBase
	add		x0, x0, #:lo12:ImageBase
	ldr		x4, [x0]
	adrp		x0, _DYNAMIC
	add		x0, x0, #:lo12:_DYNAMIC
	ldr		x0, [x0]
	ldr		x3, [sp, #16]
	ldr		x2, [sp, #24]
	mov		x1, x0
	mov		x0, x4
#else
	stp		x29, x30, [sp, #-32]!
	mov		x29, sp
	stp		x0, x1, [sp, #16]
	mov		x2, x0
	mov		x3, x1
	adr		x0, ImageBase
	adrp		x1, _DYNAMIC
	add		x1, x1, #:lo12:_DYNAMIC
	bl		_relocate
	cbnz		x0, 0f

	ldp		x0, x1, [sp, #16]
	bl		_entry

	.loc 1 __LINE__ 1 epilogue_begin
0:	ldp		x29, x30, [sp], #32
	ret
#endif
	.size _start, .-_start
.Letext:

	/*
	 * We have to have a some kind of relocations, or else the loader
	 * doesn't believe this is position independent, and will try to load
	 * us at e.g.  0x1000, which will fail.
	 */
	// hand-craft a dummy .reloc section so EFI knows it's a relocatable executable:
	.data
.dummy0:
.dummy1:
	.long	0

#define IMAGE_REL_ABSOLUTE	0
	.section .reloc, "aM", @note, 10
	.long	.dummy1-.dummy0				// Page RVA
	.long	10					// Block Size (2*4+2)
	.short	(IMAGE_REL_ABSOLUTE<<12) +  0		// reloc for dummy

DEBUG_INFO_HEADER(.Ltext, .Letext, _start,
		  .Ldbg_producer, .Ldbg_dir, .Ldbg_file);
DEBUG_INFO_FUNCTION(2, 30, _start, .Letext, .Ldbg_start);
DEBUG_INFO_FOOTER();
DEBUG_ABBREV_HEADER();
DEBUG_ABBREV_FUNCTION(2);
DEBUG_ABBREV_END();
DEBUG_INFO_STR(.Ldbg_producer, "gnu-efi");
DEBUG_INFO_STR(.Ldbg_dir, "./aa64/gnuefi");
DEBUG_INFO_STR(.Ldbg_file, __FILE__);
DEBUG_INFO_STR(.Ldbg_start, "_start");
