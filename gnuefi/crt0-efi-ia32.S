/* crt0-efi-ia32.S - x86 EFI startup code.
   Copyright (C) 1999 Hewlett-Packard Co.
	Contributed by David Mosberger <davidm@hpl.hp.com>.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials
      provided with the distribution.
    * Neither the name of Hewlett-Packard Co. nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
    CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
    BE LIABLE FOR ANYDIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
    THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
#include <dwarf.h>

	.arch i686
	.loc_mark_labels 1

	.text
.Ltext:
	.align 4

	.globl _start
_start:
	pushl %ebp
	movl %esp,%ebp

	pushl 12(%ebp)			# copy "image" argument
	pushl  8(%ebp)			# copy "systab" argument

	call 0f
0:	popl %eax
	movl %eax,%ebx

	addl $ImageBase-0b,%eax		# %eax = ldbase
	addl $_DYNAMIC-0b,%ebx		# %ebx = _DYNAMIC

	pushl %ebx			# pass _DYNAMIC as second argument
	pushl %eax			# pass ldbase as first argument
	call _relocate
	popl %ebx
	popl %ebx
	testl %eax,%eax
	jne .Lexit
  
	call _entry			# call app with "image" and "systab" argument

.Lexit:	leave
	ret
.Letext:
	.size _start, .-_start
 
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
	.section .reloc, "", @0
	.long	.dummy1-.dummy0				// Page RVA
	.long	10					// Block Size (2*4+2)
	.word	(IMAGE_REL_ABSOLUTE<<12) +  0		// reloc for dummy

DEBUG_INFO_HEADER(.Ltext, .Letext, _start,
		  .Ldbg_producer, .Ldbg_dir, .Ldbg_file);
DEBUG_INFO_FUNCTION(2, 46, _start, .Letext, .Ldbg_start);
DEBUG_INFO_LABEL(3, 72, .Lexit, .Ldbg_Lexit);
DEBUG_INFO_FOOTER();
DEBUG_ABBREV_HEADER();
DEBUG_ABBREV_FUNCTION(2);
DEBUG_ABBREV_LABEL(3);
DEBUG_ABBREV_END();
DEBUG_INFO_STR(.Ldbg_producer, "gnu-efi");
DEBUG_INFO_STR(.Ldbg_file, __FILE__);
DEBUG_INFO_STR(.Ldbg_dir, "./ia32/gnuefi");
DEBUG_INFO_STR(.Ldbg_start, "_start");
DEBUG_INFO_STR(.Ldbg_Lexit, ".Lexit");
