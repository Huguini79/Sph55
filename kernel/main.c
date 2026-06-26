#include "include/kernel.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/console.h"
#include "include/unistd.h"
#include "include/sched.h"
#include "include/mm.h"

void kernel_main()
{
    ConsoleInstall();
    GdtInstall();
    IdtInstall();

    __asm__ volatile (
        "mov $0x18, %ax\n\t"
        "ltr %ax\n\t"
    );

    printk("# ");

    // init_paging();
    // enablePaging();

    // sleep(3);

    while (1)
    {
        __asm__ volatile ("sti");
    }

}