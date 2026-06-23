#include "include/kernel.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/console.h"

void kernel_main()
{
    GdtInstall();
    IdtInstall();
    ConsoleInstall();
    printk("Welcome to SPH55 Operating System from Scratch\n\n> ");

    while (1)
    {
        __asm__ volatile ("sti");
    }

}