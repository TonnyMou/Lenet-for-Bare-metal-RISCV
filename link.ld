OUTPUT_ARCH(riscv)

ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x800000, LENGTH = 512K  /* 全部放入RAM，避免ROM与RAM跳转过远 */
}

SECTIONS
{
  /* Text section: 代码 + 只读数据 */
  .text : ALIGN(4)
  {
    PROVIDE(_text_start = .);
    *(.text.init)        /* 启动代码 */
    *(.text)             /* 正常代码 */
    *(.text.*)
    *(.rodata)           /* 只读常量 */
    *(.rodata.*)
    *(.srodata*)
    PROVIDE(_text_end = .);
  } > RAM

  /* 数据段：读写数据 */
  .data : ALIGN(4)
  {
    PROVIDE(_fdata = .);
    *(.data)
    *(.data.*)
    PROVIDE(_edata = .);
  } > RAM

  /* BSS段：未初始化数据 */
  .bss : ALIGN(4)
  {
    PROVIDE(__bss_start = .);
    *(.bss)
    *(.bss.*)
    *(COMMON)
    PROVIDE(__bss_end = .);
  } > RAM

  /* 堆分配区域 */
  . = ALIGN(8);
  PROVIDE(__heap_start = .);
  . = . + 0x4000;     /* 16KB heap空间 */
  PROVIDE(__heap_end = .);

  /* 栈空间：放在末尾 */
  . = ALIGN(8);
  .stack (NOLOAD) : ALIGN(8)
  {
    PROVIDE(__stack_bottom = .);
    . = . + 0x8000;   /* 32KB stack空间 */
    PROVIDE(__stack_top = .);
  } > RAM
}

