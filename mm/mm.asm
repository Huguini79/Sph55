BITS 32

%define PG_BIT (1 << 31)

section .text

global enablePaging
global loadPageDirectory

enablePaging:
    mov ebx, cr0
    or ebx, PG_BIT
    mov cr0, ebx
    ret

loadPageDirectory:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov cr3, eax
    pop ebp
    ret