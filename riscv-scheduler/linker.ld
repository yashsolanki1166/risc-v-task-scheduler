OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram   (wxa) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
  .text : {
    PROVIDE(_text_start = .);
    *(.text .text.*)
    PROVIDE(_text_end = .);
  } > ram

  .rodata : {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  } > ram

  .data : {
    . = ALIGN(4096);
    PROVIDE(__global_pointer$ = . + 0x800);
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*)
    *(.data .data.*)
    PROVIDE(_data_end = .);
  } > ram

  .bss : {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*)
    *(.bss .bss.*)
    *(COMMON)
    PROVIDE(_bss_end = .);
  } > ram

  PROVIDE(_memory_start = ORIGIN(ram));
  PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));
  PROVIDE(_heap_start = _bss_end);
}
