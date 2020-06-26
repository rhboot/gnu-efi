/* reloc_x64.c - position independent x86_64 ELF shared object relocator
   Copyright (C) 1999 Hewlett-Packard Co.
	Contributed by David Mosberger <davidm@hpl.hp.com>.
   Copyright (C) 2005 Intel Co.
	Contributed by Fenghua Yu <fenghua.yu@intel.com>.

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

#include <efi.h>
#include <efilib.h>

#include <stddef.h>

#include <elf.h>

#define EFI_DEBUG

static const wchar_t hex[] = L"0123456789abcdef";

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

#ifdef EFI_DEBUG
#define printval(a) printval_(systab, sizeof(a), (uint64_t)(a))
#define print(x) print_(systab, (x))
#else
#define printval(a)
#define print(x)
#endif

EFI_STATUS _relocate (unsigned long ldbase, Elf64_Dyn *dyn,
		      EFI_HANDLE image EFI_UNUSED,
		      EFI_SYSTEM_TABLE *systab EFI_UNUSED)
{
	long relsz = 0, relent = 0;
	Elf64_Rel *rel = 0;
	unsigned long *addr;
	int i;

	for (i = 0; dyn[i].d_tag != DT_NULL; ++i) {
		print(L"i:"); printval(i);
		print(L"dyn[i].d_tag:"); printval(dyn[i].d_tag);
		switch (dyn[i].d_tag) {
			case DT_RELA:
				rel = (Elf64_Rel*)
					((unsigned long)dyn[i].d_un.d_ptr
					 + ldbase);
				print(L"rel:   "); printval(rel);
				break;

			case DT_RELASZ:
				relsz = dyn[i].d_un.d_val;
				print(L"relsz: "); printval(relsz);
				break;

			case DT_RELAENT:
				relent = dyn[i].d_un.d_val;
				print(L"relent:"); printval(relent);
				break;

			default:
				break;
		}
	}

        if (!rel && relent == 0) {
		print(L"!rel && relent == 0\r\n");
                return EFI_SUCCESS;
	}

	if (!rel || relent == 0) {
		print(L"!rel || relent == 0\r\n");
		return EFI_LOAD_ERROR;
	}

	while (relsz > 0) {
		/* apply the relocs */
		switch (ELF64_R_TYPE (rel->r_info)) {
			case R_X86_64_NONE:
				break;

			case R_X86_64_RELATIVE:
				addr = (unsigned long *)
					(ldbase + rel->r_offset);
				print(L"addr:"); printval(addr);
				print(L"*addr:"); printval(*addr);
				*addr += ldbase;
				print(L"new *addr:"); printval(*addr);
				break;

			default:
				break;
		}
		rel = (Elf64_Rel*) ((char *) rel + relent);
		relsz -= relent;
	}
	print(L"returning success\r\n");
	return EFI_SUCCESS;
}
