BITS 32

%define PG_BIT (1 << 31)

section .text

global enablePaging
global loadPageDirectory
extern page_directory

enablePaging:
    mov ebx, cr0
    or ebx, PG_BIT
    mov cr0, ebx
    jmp .flush_pipeline
.flush_pipeline:
    ret

loadPageDirectory:
    mov eax, page_directory
    mov cr3, eax
    ret