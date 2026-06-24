#include "include/kernel.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/console.h"
#include "include/unistd.h"

void kernel_main()
{
    GdtInstall();
    IdtInstall();
    ConsoleInstall();

    printk("# ");

    // sleep(3);

    __asm__ volatile (
        "mov $0x18, %ax\n\t"
        "ltr %ax\n\t"
    );

    while (1)
    {
        __asm__ volatile ("sti");
    }

}