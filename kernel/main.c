#include "include/kernel.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/console.h"
#include "include/unistd.h"
#include "include/sched.h"
#include "include/mm.h"

struct pcb* newProcess;
struct pcb* newProc;
struct pcb* process3;

void funct3()
{
    char buf[16];
    printk("TASK3: I am the third process! | PID=");
    pid_t pid = getCurrentPID();
    itoa(pid, buf, 10);
    printk(buf);
    printk("\n");
    while (1) {}
}

void funct2()
{
    char buf[16];
    printk("TASK2: I am the second process! | PID=");
    pid_t pid = getCurrentPID();
    itoa(pid, buf, 10);
    printk(buf);
    printk("\n");
    while (1) {}

    // switch_to(newProcess);
    // printk("\nTASK2: I'm back");
    // switch_to(newProcess);
}

void funct()
{
    char buf[16];
    printk("TASK1: Hello World! | PID=");
    pid_t pid = getCurrentPID();
    itoa(pid, buf, 10);
    printk(buf);
    printk("\n");
    while (1) {}
    // yield();
}

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

    newProcess = createProcess(1, (uint32_t)funct);
    newProc = createProcess(2, (uint32_t)funct2);
    process3 = createProcess(3, (uint32_t)funct3);

    // init_paging();
    // enablePaging();

    // sleep(3);

    while (1)
    {
        __asm__ volatile ("sti");
    }

}