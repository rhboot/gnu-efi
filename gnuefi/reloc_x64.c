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
	wchar_t buf[19] = L"0x0000000000000000";
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

	// value = 0x00000070
	// shift = 12
	// i = 16
	// mask = ~((1<<16)-1) = ~(0x10000-1) = ~0xffff = 0xffff0000
	// mask & value = 0x00000000
	// i = 12
	// mask = ~((1<<12)-1) = ~(0x1000-1) = ~0xfff = 0xfffff000
	// mask & value = 0x00000000
	// i = 8
	// mask = ~((1<<8)-1) = ~(0x100-1) = ~0xff = 0xffffff00
	// mask & value = 0x00000000
	// i = 4
	// mask = ~((1<<4)-1) = ~(0x10-1) = ~0xf = 0xfffffff0
	// mask & value = 0x000000b0
	// i = 8
	// break

	for (i = shift + 4; i > 4; i -= 4) {
		mask = ~((1 << i) - 1);
		if (value & mask) {
			i += 4;
			break;
		}
	}
	shift = i;
#if 0
	if (!(value & 0xffffffffffffff00ull) && shift > 4)
		shift = 4;
	else if (!(value & 0xffffffffffff0000ull) && shift > 12)
		shift = 12;
	else if (!(value & 0xffffffffff000000ull) && shift > 20)
		shift = 20;
	else if (!(value & 0xffffffff00000000ull) && shift > 28)
		shift = 28;
	else if (!(value & 0xffffff0000000000ull) && shift > 36)
		shift = 36;
	else if (!(value & 0xffff000000000000ull) && shift > 44)
		shift = 44;
	else if (!(value & 0xff00000000000000ull) && shift > 52)
		shift = 52;
#endif

	mask = 0xfull << shift;

	for (i = 2; mask != 0; i += 2) {
		buf[i] = hex[(value & mask) >> shift];
		mask >>= 4;
		shift -= 4;
		buf[i+1] = hex[(value & mask) >> shift];
		mask >>= 4;
		shift -= 4;
	}
	buf[i+0] = L'\000';

	systab->ConOut->OutputString(systab->ConOut, buf);
}

static void
__attribute__((__unused__))
print_(EFI_SYSTEM_TABLE *systab, wchar_t *str)
{
	systab->ConOut->OutputString(systab->ConOut, str);
}

#if 0
#define _STRING(x) #x
#define STRING(x) _STRING(x)
#define CONCAT(x,y) x ## y

#define STARTSTOP(x,y) \
		".weakref _" STRING(x) ", _start_." STRING(y) "\n" \
		".weakref _e" STRING(x) ", _stop_." STRING(y) "\n"
__asm__ (
STARTSTOP(text, text)
STARTSTOP(reloc, reloc)
STARTSTOP(data, data)
STARTSTOP(bss, bss)
STARTSTOP(rodata, rodata)
STARTSTOP(data_rel, data.rel)
STARTSTOP(data_rel_local, data.rel.local)
STARTSTOP(data_rel_ro, data.rel.ro)
STARTSTOP(data_rel_ro_local, data.rel.ro.local)
STARTSTOP(data_rela, data.rela)
STARTSTOP(data_rela_local, data.rela.local)
STARTSTOP(data_rela_ro, data.rela.ro)
STARTSTOP(data_rela_ro_local, data.rela.ro.local)
STARTSTOP(dynsym, dynsym)
STARTSTOP(dynstr, dynstr)
STARTSTOP(rel, rel)
STARTSTOP(rela, rela)
STARTSTOP(dynamic, dynamic)
STARTSTOP(eh_frame_hdr, eh_frame_hdr)
STARTSTOP(eh_frame, eh_frame)
);
#endif


extern uint8_t
	_text, _etext,
	_reloc, _ereloc,
	_data, _edata,
	_bss, _ebss,
	_rodata, _erodata,
#if 0
	_data_rel, _edata_rel,
	_data_rel_local, _edata_rel_local,
	_data_rel_ro, _edata_rel_ro,
	_data_rel_ro_local, _edata_rel_ro_local,
#endif
	_dynsym, _edynsym,
	_dynstr, _edynstr,
#if 0
	_data_ident, _edata_ident,
	_rel, _erel,
	_rela, _erela,
#endif
	_dynamic, _edynamic,
	_note_gnu_build_id, _enote_gnu_build_id,
	_eh_frame_hdr, _eeh_frame_hdr,
	_eh_frame, _eeh_frame
	;

static struct {
	void *begin;
	void *end;
	wchar_t name[32];
} _sections[] = {
	{ &_text, &_etext, L".text" },
	{ &_reloc, &_ereloc, L".relocl" },
	{ &_data, &_edata, L".data" },
	{ &_bss, &_ebss, L".bss" },
	{ &_rodata, &_erodata, L".rodata" },
#if 0
	{ &_data_rel, &_edata_rel, L".data.rel" },
	{ &_data_rel_local, &_edata_rel_local, L".data.rel.local" },
	{ &_data_rel_ro, &_edata_rel_ro, L".data.rel.ro" },
	{ &_data_rel_ro_local, &_edata_rel_ro_local, L".data.rel.ro.local" },
#endif
	{ &_dynsym, &_edynsym, L".dynsym" },
	{ &_dynstr, &_edynstr, L".dynstr" },
#if 0
	{ &_data_ident, &_edata_ident, L".data.ident" },
	{ &_rel, &_erel, L".rel" },
	{ &_rela, &_erela, L".rela" },
#endif
	{ &_dynamic, &_edynamic, L".dynamic" },
	{ &_note_gnu_build_id, &_enote_gnu_build_id, L".note.gnu.build-id" },
	{ &_eh_frame_hdr, &_eeh_frame_hdr, L".eh_frame_hdr" },
	{ &_eh_frame, &_eeh_frame, L".eh_frame" },
	{ NULL, NULL, L"" }
};

static void
__attribute__((__unused__))
printsection_(EFI_SYSTEM_TABLE *systab, uint64_t addr)
{
	unsigned int i;
	void *obj = (void *)addr;
	for (i = 0; _sections[i].name[0] != L'\0'; i++) {
		if (_sections[i].begin >= obj && _sections[i].end <= obj) {
			print_(systab, _sections[i].name);
			return;
		}
	}
	print_(systab, L"unknown section");
}

#ifdef EFI_DEBUG
#define printval(a) printval_(systab, sizeof(a), (uint64_t)(a))
#define print(x) print_(systab, (x))
#define printsection(obj) printsection_(systab, obj)
#else
#define printval(a)
#define print(x)
#define printsection(obj)
#endif

extern uint8_t ImageBase;

EFI_STATUS EFIAPI _relocate (unsigned long ldbase, Elf64_Dyn *dyn,
			     EFI_HANDLE image EFI_UNUSED,
			     EFI_SYSTEM_TABLE *systab EFI_UNUSED)
{
	Elf64_Rela *rela = 0;
	uint64_t relasz = 0, relaent = 0;
	uint64_t relsz = 0, relent = 0;
	Elf64_Rel *rel = 0;
	unsigned long *addr = NULL;
	int i;

	print(L" ldbase:"); printval(ldbase);
	print(L" dyn:"); printval(dyn);
	print(L" img:"); printval(image);
	print(L" systab:"); printval(systab);
	print(L"\r\n");
	for (i = 0; dyn[i].d_tag != DT_NULL; ++i) {
		print(L"i:"); printval(i);
		print(L" tag:"); printval(dyn[i].d_tag);
		print(L" ");
		switch (dyn[i].d_tag) {
		case DT_NULL:
			print(L"DT_NULL");
			break;
		case DT_NEEDED:
			print(L"DT_NEEDED:   ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_PLTRELSZ:
			print(L"DT_PLTRELSZ: ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_PLTGOT:
			print(L"DT_PLTGOT:   ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_HASH:
			print(L"DT_HASH:     ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_STRTAB:
			print(L"DT_STRTAB:   ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_SYMTAB:
			print(L"DT_SYMTAB:   ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_RELA:
			rela = (Elf64_Rela*)
				((unsigned long)dyn[i].d_un.d_ptr
				 + ldbase);
			print(L"DT_RELA:     ");
			printval((unsigned long)dyn[i].d_un.d_ptr);
			print(L"+ldbase->");
			printval(rela);
			break;
		case DT_RELASZ:
			relasz = dyn[i].d_un.d_val;
			print(L"DT_RELASZ:   ");
			printval(relasz);
			break;
		case DT_RELAENT:
			relaent = dyn[i].d_un.d_val;
			print(L"DT_RELAENT:  ");
			printval(relaent);
			break;
		case DT_STRSZ:
			print(L"DT_STRSZ:    ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_SYMENT:
			print(L"DT_SYMENT:   ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_INIT:
			print(L"DT_INIT:     ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_FINI:
			print(L"DT_FINI:     ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_SONAME:
			print(L"DT_SONAME:   ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_RPATH:
			print(L"DT_RPATH:    ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_SYMBOLIC:
			print(L"DT_SYMBOLIC");
			break;
		case DT_REL:
			rel = (Elf64_Rel*)
				((unsigned long)dyn[i].d_un.d_ptr
				 + ldbase);
			print(L"DT_REL:     ");
			printval((unsigned long)dyn[i].d_un.d_ptr);
			print(L"+ldbase->");
			printval(rel);
			break;
		case DT_RELSZ:
			relsz = dyn[i].d_un.d_val;
			print(L"DT_RELSZ:   ");
			printval(relsz);
			break;
		case DT_RELENT:
			relent = dyn[i].d_un.d_val;
			print(L"DT_RELENT:  ");
			printval(relent);
			break;
		case DT_PLTREL:
			print(L"DT_PLTREL:   ");
			printval(dyn[i].d_un.d_val);
			break;
		case DT_DEBUG:
			print(L"DT_DEBUG:    ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_TEXTREL:
			print(L"DT_TEXTREL");
			break;
		case DT_JMPREL:
			print(L"DT_JMPREL:   ");
			printval(dyn[i].d_un.d_ptr);
			break;
		case DT_BIND_NOW:
			print(L"DT_BIND_NOW");
			break;
		case DT_LOPROC:
			print(L"DT_LOPROC:   ");
			printval((uint32_t)0x70000000u);
			break;
		case DT_HIPROC:
			print(L"DT_HIPROC:   ");
			printval((uint32_t)0x7fffffffu);
			break;
		default:
			print(L"UNKNOWN:     ");
			printval(dyn[i].d_un.d_val);
			break;
		}
		print(L"\r\n");
	}

	if (!rel && !rela && relent == 0 && relaent == 0) {
		print(L"!rela && relaent == 0 && !rel && relent == 0\r\n");
		return EFI_SUCCESS;
	}

	if ((!rel || relent == 0) && (!rela || relaent == 0)) {
		if (!rela && relaent == 0)
			print(L"!rela || relaent == 0\r\n");
		if (!rel && relent == 0)
			print(L"!rel || relent == 0\r\n");
		return EFI_LOAD_ERROR;
	}

	while (relasz > 0) {
		/* apply the relocs */
		switch (ELF64_R_TYPE (rela->r_info)) {
			case R_X86_64_NONE:
				addr = (unsigned long *)
					(ldbase + rela->r_offset);
				print(L"NONE");
				print(L" offset:"); printval(rela->r_offset);
				print(L" *rela:"); printval(*addr);
				print(L" +addend:"); printval(rela->r_addend);
				print(L" "); printsection(*addr);
				break;

			case R_X86_64_RELATIVE:
				addr = (unsigned long *)
					(ldbase + rela->r_offset);
				print(L"RELA");
				print(L" offset:"); printval(rela->r_offset);
				print(L" *rela:"); printval(*addr);
				print(L" +addend:"); printval(rela->r_addend);
				print(L"->");
				*addr += ldbase;
				*addr += rela->r_addend;
				printval(*addr);
				print(L" "); printsection(*addr - ldbase);
				break;

			default:
				print(L"???? tag:");
				printval(dyn[i].d_tag);
				print(L" offset:");
				printval(rela->r_offset);
				print(L" "); printsection(rela->r_offset);
				break;
		}
		print(L"\r\n");
		rela = (Elf64_Rela*) ((char *) rela + relaent);
		relasz -= relaent;
	}

	while (relsz > 0) {
		/* apply the relocs */
		switch (ELF64_R_TYPE (rel->r_info)) {
			case R_X86_64_NONE:
				addr = (unsigned long *)
					(ldbase + rel->r_offset);
				print(L"NONE");
				print(L" offset:"); printval(rel->r_offset);
				print(L" *rel:"); printval(*addr);
				print(L" "); printsection(*addr);
				break;

			case R_X86_64_RELATIVE:
				addr = (unsigned long *)
					(ldbase + rel->r_offset);
				print(L"REL");
				print(L" offset:"); printval(rel->r_offset);
				print(L" *rel:"); printval(*addr);
				print(L"->");
				*addr += ldbase;
				printval(*addr);
				print(L" "); printsection(*addr - ldbase);
				break;

			default:
				print(L"???? tag:");
				printval(dyn[i].d_tag);
				print(L" offset:");
				printval(rel->r_offset);
				print(L" "); printsection(rel->r_offset);
				break;
		}
		print(L"\r\n");
		rel = (Elf64_Rel*) ((char *) rel + relent);
		relsz -= relent;
	}
	print(L"zeroing ");
	printval(&_ebss - &_bss);
	print(L" bytes of .bss at ");
	printval(&_bss);
	print(L"\r\n");
	ZeroMem(&_bss, &_ebss - &_bss);

	print(L"returning success\r\n");
	return EFI_SUCCESS;
}
