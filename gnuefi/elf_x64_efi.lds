/* Same as elf_x64_fbsd_efi.lds, except for OUTPUT_FORMAT below - KEEP IN SYNC */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
PHDRS
{
  load PT_LOAD FLAGS(7);
  dynamic PT_DYNAMIC FLAGS(6);
  note PT_NOTE FLAGS(4);
  stack 7 FLAGS(6);
}
SECTIONS
{
  . = 0;
  ImageBase = .;

  .text 0x1000 : ALIGN(4096)
  {
    _text = .;
    *(.init)
    _start = .;
    *(.text)
    *(.text.*)
    *(.fini)
    *(.plt)
    *(.plt.got)
    *(.gnu.linkonce.t.*)
    . = ALIGN(4096);
    _etext = .;
    _text_size = _etext - _text;
  } :load

  /*
   * We have to have a some kind of relocations, or else the loader doesn't
   * believe this is position independent, and will try to load us at e.g.
   * 0x1000, which will fail.
   */
  .reloc ALIGN(4096) : ALIGN(4096)
  {
    _reloc = .;
    *(.reloc)
    _ereloc = .;
    _reloc_size = _ereloc - _reloc;
  } :load

  .data ALIGN(4096) : ALIGN(4096)
  {
    _data = .;
    *(.data)
    *(.data1)
    *(.sdata)
    *(.got)
    *(.got.plt)
    . = ALIGN(4096);
    _edata = .;
    _data_size = _edata - _data;
  } :load

  .bss ALIGN(4096) (NOLOAD) : ALIGN(4096)
  {
    _bss = .;
    *(.sbss)
    *(.scommon)
    *(.dynbss)
    *(.bss)
    *(COMMON)
    . = ALIGN(4096);
    _ebss = .;
    _bss_size = _ebss - _bss;
  } :load

  .rodata ALIGN(4096) : ALIGN(4096)
  {
    _rodata = .;
    *(.rodata*)
    *(.srodata*)

    /*
     * Note that these aren't the using the GNU "CONSTRUCTOR" output section
     * command, so they don't start with a size.  Because of p2align and the
     * end/END definitions, and the fact that they're mergeable, they can also
     * have NULLs which aren't guaranteed to be at the end.
     */
    . = ALIGN(16);
    _init_array = .;
    *(SORT_BY_INIT_PRIORITY(.init_array*))
    FILL(0x0);
    . = ALIGN(16);
    _init_array_end = .;
    __CTOR_LIST__ = .;
    *(SORT_BY_NAME(.ctors))
    FILL(0x0);
    . = ALIGN(16);
    __CTOR_END__ = .;
    __DTOR_LIST__ = .;
    *(SORT_BY_NAME(.dtors))
    FILL(0x0);
    . = ALIGN(16);
    __DTOR_END__ = .;
    _fini_array = .;
    *(SORT_BY_INIT_PRIORITY(.fini_array*))
    FILL(0x0);
    . = ALIGN(16);
    _fini_array_end = .;

    . = ALIGN(4096);
    _erodata = .;
    _rodata_size = _erodata - _rodata;
  } :load

  .data.rel ALIGN(512) : ALIGN(512)
  {
    _data_rel = .;
    *(.data.rel)
    . = ALIGN(512);
    _edata_rel = .;
    _data_rel_size = _edata_rel - _data_rel;
  } :load

  .data.rel.local ALIGN(512) : ALIGN(512)
  {
    _data_rel_local = .;
    *(.data.rel.local)
    . = ALIGN(512);
    _edata_rel_local = .;
    _data_rel_local_size = _edata_rel_local - _data_rel_local;
  } :load

  .data.rel.ro ALIGN(512) : ALIGN(512)
  {
    _data_rel_ro = .;
    *(.data.rel.ro)
    . = ALIGN(512);
    _edata_rel_ro = .;
    _data_rel_ro_size = _edata_rel_ro - _data_rel_ro;
  } :load

  .data.rel.ro.local ALIGN(512) : ALIGN(512)
  {
    _data_rel_ro_local = .;
    *(.data.rel.ro.local)
    . = ALIGN(512);
    _edata_rel_ro_local = .;
    _data_rel_ro_local_size = _edata_rel_ro_local - _data_rel_ro_local;
  } :load

  .data.ident ALIGN(512) : ALIGN(512)
  {
    _data_ident = .;
    *(.data.ident)
    . = ALIGN(512);
    _edata_ident = .;
    _data_ident_size = _edata_ident - _data_ident;
  } :load =0xa5a5a5a5

  .eh_frame_hdr ALIGN(512) : ALIGN(512)
  {
    _eh_frame_hdr = .;
    *(.eh_frame_hdr)
    . = ALIGN(512);
    _eeh_frame_hdr = .;
    _eh_frame_hdr_size = _eeh_frame_hdr - _eh_frame_hdr;
  } :load

  .eh_frame ALIGN(512) : ALIGN(512)
  {
    _eh_frame = .;
    *(.eh_frame)
    . = ALIGN(512);
    _eeh_frame = .;
    _eh_frame_size = _eeh_frame - _eh_frame;
  } :load

  .dynamic ALIGN(4096) : ALIGN(4096)
  {
    _dynamic = .;
    *(.dynamic)
    . = ALIGN(4096);
    _edynamic = .;
    _dynamic_size = _edynamic - _dynamic;
  } :load

  .hash :
  {
    *(.hash)
  } :load

  .gnu.hash :
  {
    *(.gnu.hash)
  } :load

  .dynstr ALIGN(4096) : ALIGN(4096)
  {
    _dynstr = .;
    *(.dynstr)
    . = ALIGN(4096);
    _edynstr = .;
    _dynstr_size = _edynstr - _dynstr;
  } :load

  .dynsym ALIGN(4096) : ALIGN(4096)
  {
    _dynsym = .;
    *(.dynsym)
    . = ALIGN(4096);
    _edynsym = .;
    _dynsym_size = _edynsym - _dynsym;
  } :load

  .rela ALIGN(4096) : ALIGN(4096)
  {
    _rela = .;
    *(.rela)
    *(.rela.*)
    _erela = .;
    _rela_size = _erela - _rela;
  } :load

  .rel ALIGN(4096) : ALIGN(4096)
  {
    _rel = .;
    *(.rel)
    *(.rel.*)
    _erel = .;
    _rel_size = _erel - _rel;
  } :load

  .note.gnu.build-id ALIGN(512) : ALIGN(512)
  {
    _note_gnu_build_id = .;
    *(.note.gnu.build-id)
    . = ALIGN(512);
    _enote_gnu_build_id = .;
    _note_gnu_build_id_size = _enote_gnu_build_id - _note_gnu_build_id;
  } :load

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  /* .debug ALIGN(4096) (NOLOAD) : ALIGN(4096) { *(.debug) } :NONE */
  /* .line              (NOLOAD) : { *(.line) } :NONE */
  /* GNU DWARF 1 extensions */
  /* .debug_aranges     (NOLOAD) : { *(.debug_aranges) } :NONE */
  /* .debug_srcinfo     (NOLOAD) : { *(.debug_srcinfo) } :NONE */
  /* .debug_sfnames     (NOLOAD) : { *(.debug_sfnames) } :NONE */
  /* .debug_pubnames    (NOLOAD) : { *(.debug_pubnames) } :NONE */

  /* DWARF 2 */
  .debug_info        (NOLOAD) : { *(.debug_info) } :NONE
  .debug_abbrev      (NOLOAD) : { *(.debug_abbrev) } :NONE
  .debug_aranges     (NOLOAD) : { *(.debug_aranges) } :NONE
  .debug_ranges      (NOLOAD) : { *(.debug_ranges) } :NONE
  .debug_line        (NOLOAD) : { *(.debug_line) } :NONE
  .debug_str         (NOLOAD) : { *(.debug_str) } :NONE

  .debug_frame       (NOLOAD) : { *(.debug_frame) } :NONE
  .debug_loc         (NOLOAD) : { *(.debug_loc) } :NONE
  .debug_macinfo     (NOLOAD) : { *(.debug_macinfo) } :NONE
  .debug_macro       (NOLOAD) : { *(.debug_macro*) } :NONE

  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames   (NOLOAD) : { *(.debug_weaknames) } :NONE
  .debug_funcnames   (NOLOAD) : { *(.debug_funcnames) } :NONE
  .debug_typenames   (NOLOAD) : { *(.debug_typenames) } :NONE
  .debug_varnames    (NOLOAD) : { *(.debug_varnames) } :NONE

  /DISCARD/ :
  {
    *(.note.GNU-stack)
    *(.GCC.command.line)
    *(.gnu.version_d)
    *(.gnu.version_r)
    *(.gnu.version)
    *(.comment)
  }
}
