BITS 32

section .bss
align 4
stack_bottom:
    resb 65536 ; 64 Kilobytes
stack_top:

section .text

align 4
dd 0x1BADB002
dd 0x00
dd - (0x1BADB002 + 0x00)

global start
global remapPIC
extern kernel_main

start:
    cli
    mov esp, stack_top
    call remapPIC
    call kernel_main
    hlt

remapPIC:
    ; ICW 1
    mov al, 0x11
    out 0x20, al
    out 0xA0, al

    ; ICW 2
    mov al, 0x20
    out 0x21, al

    mov al, 0x28
    out 0xA1, al

    ; ICW 3
    mov al, 0x4
    out 0x21, al

    mov al, 0x2
    out 0xA1, al

    ; ICW 4
    mov al, 1
    out 0x21, al
    out 0xA1, al
    ret