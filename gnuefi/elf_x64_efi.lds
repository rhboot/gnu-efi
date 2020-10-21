/* Same as elf_x64_fbsd_efi.lds, except for OUTPUT_FORMAT below - KEEP IN SYNC */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS
{
  . = 0;
  ImageBase = .;

  .text 0x2000 : ALIGN(4096)
  {
    _start = .;
    _text = .;
    *(.text)
    *(.text.*)
    *(.plt)
    *(.plt.got)
    *(.gnu.linkonce.t.*)
    . = ALIGN(4096);
  }
  _etext = .;
  _text_size = . - _text;

  /*
   * We have to have a some kind of relocations, or else the loader doesn't
   * believe this is position independent, and will try to load us at e.g.
   * 0x1000, which will fail.
   */
  . = ALIGN(4096);
  .reloc :
  {
   *(.reloc)
  }

  .data : ALIGN(4096)
  {
   _data = .;
   *(.data*)
   *(.sdata)
   *(.srodata*)
   *(.rodata*)
   *(.got.plt)
   *(.got)

   /*
    * Note that these aren't the using the GNU "CONSTRUCTOR" output section
    * command, so they don't start with a size.  Because of p2align and the
    * end/END definitions, and the fact that they're mergeable, they can also
    * have NULLs which aren't guaranteed to be at the end.
    */
   . = ALIGN(16);
   _init_array = .;
   *(SORT_BY_NAME(.init_array))
   _init_array_end = .;
   __CTOR_LIST__ = .;
   *(SORT_BY_NAME(.ctors))
   __CTOR_END__ = .;
   __DTOR_LIST__ = .;
   *(SORT_BY_NAME(.dtors))
   __DTOR_END__ = .;
   _fini_array = .;
   *(SORT_BY_NAME(.fini_array))
   _fini_array_end = .;

   /* the EFI loader doesn't seem to like a .bss section, so we stick
      it all into .data: */
   . = ALIGN(4096);
   _bss = .;
   _bstart = .;
   *(.sbss)
   *(.scommon)
   *(.dynbss)
   *(.bss)
   *(COMMON)
   . = ALIGN(4096);
   _bss_end = .;
   _bend = .;
   _bsize = _bend - _bstart;
  }
  .note.gnu.build-id : { *(.note.gnu.build-id) }

  .dynamic : ALIGN(512) { *(.dynamic) }

  .rela :
  {
    *(.rela.dyn)
    *(.rela.got)
    *(.rela.data)
    *(.rela.data*)
    *(.rela.plt)
    *(.rela.text)
    *(.rela.ifunc)
    *(.rela.init_array)
    *(.rela.fini_array)
    *(.data.rela.ro.local)
    *(.data.rela.local)
    *(.data.rela.ro)
    *(.data.rel*)
  }
  _edata = .;
  _data_size = . - _data;

  /*
   * We have to have a some kind of relocations, or else the loader doesn't
   * believe this is position independent, and will try to load us at e.g.
   * 0x1000, which will fail.
   */
  . = ALIGN(4096);
  .reloc :
  {
   *(.reloc)
  }

  . = ALIGN(4096);
  .hash : ALIGN(1) { *(.hash) }
  .gnu.hash : ALIGN(1) { *(.gnu.hash) }
  .dynsym : ALIGN(4096) { *(.dynsym) }
  .dynstr : ALIGN(4096) { *(.dynstr) }
  .eh_frame_hdr : ALIGN(1) { *(.eh_frame_hdr) }
  .eh_frame : ALIGN(1) { *(.eh_frame) }

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  .debug_macro    0 : { *(.debug_macro*) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  /DISCARD/ :
  {
    *(.note.GNU-stack)
    *(.GCC.command.line)
    *(.gnu.version_d)
    *(.gnu.version_r)
    *(.gnu.version)
  }
  .comment 0 : { *(.comment) }
}
