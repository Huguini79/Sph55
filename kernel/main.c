#include "include/kernel.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/console.h"
#include "include/unistd.h"
#include "include/sched.h"
#include "include/mm.h"

struct pcb* newProcess;
struct pcb* newProc;

void funct2()
{
    printk("\nTASK2: Second process in execution");
    switch_to(newProcess);
}

void funct()
{
    printk("\nTASK1: Hello World!");
    newProc = createProcess(2, (uint32_t)funct2);
    switch_to(newProc);
    printk("\nTASK1: -- Second process executed with success\n# ");
    while (1)
    {
        __asm__ volatile ("sti");
    }
}

void kernel_main()
{
    __asm__ volatile ("cli");
    GdtInstall();
    IdtInstall();
    init_paging();
    // enablePaging();
    ConsoleInstall();

    printk("# ");

    __asm__ volatile (
        "mov $0x18, %ax\n\t"
        "ltr %ax\n\t"
    );

    newProcess = createProcess(1, (uint32_t)funct);
    switch_to(newProcess);

    // sleep(3);

    while (1)
    {
        __asm__ volatile ("sti");
    }

}