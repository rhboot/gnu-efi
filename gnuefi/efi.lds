SECTIONS
{
  . = 0;
  ImageBase = .;
/*
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
  }
*/
  /*
   * We have to have a some kind of relocations, or else the loader doesn't
   * believe this is position independent, and will try to load us at e.g.
   * 0x1000, which will fail.
   */
  . = SIZEOF_HEADERS;
  . = NEXT(4096);
  .reloc ALIGN(4096) : ALIGN(4096)
  {
    _reloc = .;
    /*
     * Hand-craft a dummy .reloc entry so EFI knows it's a relocatable
     * executable.
     */
    LONG(0);
    LONG(10);
    SHORT(0);
    _ereloc = .;
    _reloc_size = _ereloc - _reloc;
  }

  . = ALIGN(4096);
  _text = ADDR(.text);
  _etext = ADDR(.text) + SIZEOF(.text);
  _reloc = ADDR(.reloc);
  _ereloc = ADDR(.reloc) + SIZEOF(.reloc);
  _data = ADDR(.data);
  _edata = ADDR(.data) + SIZEOF(.data);
  _bss = ADDR(.bss);
  _ebss = ADDR(.bss) + SIZEOF(.bss);
  _rodata = ADDR(.rodata);
  _erodata = ADDR(.rodata) + SIZEOF(.rodata);
  /*
  _data.rel = ADDR(.data.rel);
  _edata.rel = ADDR(.data.rel) + SIZEOF(.data.rel);
  _data.rel.local = ADDR(.data.rel.local);
  _edata.rel.local = ADDR(.data.rel.local) + SIZEOF(.data.rel.local);
  */
  _data.rel.ro = ADDR(.data.rel.ro);
  _edata.rel.ro = ADDR(.data.rel.ro) + SIZEOF(.data.rel.ro);
  /*
  _data.rel.ro.local = ADDR(.data.rel.ro.local);
  _edata.rel.ro.local = ADDR(.data.rel.ro.local) + SIZEOF(.data.rel.ro.local);
  */
  _dynsym = ADDR(.dynsym);
  _edynsym = ADDR(.dynsym) + SIZEOF(.dynsym);
  _dynstr = ADDR(.dynstr);
  _edynstr = ADDR(.dynstr) + SIZEOF(.dynstr);
  /*
  _rel = ADDR(.rel);
  _erel = ADDR(.rel) + SIZEOF(.rel);
  _rela = ADDR(.rela);
  _erela = ADDR(.rela) + SIZEOF(.rela);
  */
  _dynamic = ADDR(.dynamic);
  _edynamic = ADDR(.dynamic) + SIZEOF(.dynamic);
  _eh_frame_hdr = ADDR(.eh_frame_hdr);
  _eeh_frame_hdr = ADDR(.eh_frame_hdr) + SIZEOF(.eh_frame_hdr);
  _eh_frame = ADDR(.eh_frame);
  _eeh_frame = ADDR(.eh_frame) + SIZEOF(.eh_frame);
  _note_gnu_build_id = ADDR(.note.gnu.build-id);
  _enote_gnu_build_id = ADDR(.note.gnu.build-id) + SIZEOF(.note.gnu.build-id);

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
/* INSERT BEFORE .note.gnu.build-id; */
INSERT BEFORE .hash;
