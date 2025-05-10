.section .text.init
.globl _start
_start:
    # 只清零 BSS 段
    la a0, __bss_start
    la a1, __bss_end

clear_loop:
    beq a0, a1, call_main
    sw zero, 0(a0)
    addi a0, a0, 4
    j clear_loop

call_main:
    call main

hang:
    j hang

