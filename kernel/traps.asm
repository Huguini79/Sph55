BITS 32

section .text

global pit_handler_stub
extern pit_handler

pit_handler_stub:
    pushad
    call pit_handler
    popad
    iretd