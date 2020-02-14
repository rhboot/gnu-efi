OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
  . = 0;
  ImageBase = .;
  .hash : { *(.hash) }
  .gnu.hash : { *(.gnu.hash) }
  .eh_frame : { *(.eh_frame) }

  .text : ALIGN(4096)
  {
    _start = .;
    _text = .;
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    *(.srodata*)
    *(.rodata*)
    . = ALIGN(4096);
  }
  _etext = .;
  _text_size = . - _text;

  /*
   * We have to have a some kind of relocations, or else the loader doesn't
   * believe this is position independent, and will try to load us at e.g.
   * 0x1000, which will fail.
   */
  /*
  . = ALIGN(4096);
  .reloc :
  {
   *(.reloc)
  }
  */

  .dynamic : { *(.dynamic) }
  .data : ALIGN(4096)
  {
   _data = .;
   *(.data*)
   *(.sdata)
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
   *(.sbss)
   *(.scommon)
   *(.dynbss)
   *(.bss)
   *(COMMON)
   *(.rel.local)
   . = ALIGN(4096);
   _bss_end = .;
  }
  .note.gnu.build-id : { *(.note.gnu.build-id) }

  .rela.dyn : { *(.rela.dyn) }
  .rela.got : { *(.rela.got) }
  .rela.data : { *(.rela.data) *(.rela.data*) }
  _edata = .;
  _data_size = . - _data;

  . = ALIGN(4096);
  .dynsym : ALIGN(4096) { *(.dynsym) }
  . = ALIGN(4096);
  .dynstr : ALIGN(4096) { *(.dynstr) }
  . = ALIGN(4096);
  .ignored.reloc :
  {
    *(.note.GNU-stack)
  }
  .comment 0 : { *(.comment) }
}
