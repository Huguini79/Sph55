#include <stdint.h>
#include <stddef.h>

#include "include/console.h"
#include "include/io.h"
#include "include/keyboard.h"
#include "include/sched.h"
#include "include/string.h"

struct Idt
{
    uint16_t isr_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t type_attributes;
    uint16_t isr_high;

} __attribute__((packed));

struct Idtr
{
    uint16_t limit;
    uint32_t base;

} __attribute__((packed));

struct Idtr Idtr;

struct Idt idt_table[256] __attribute__((aligned(8)));

void setIdtDescriptor(int vector, int type_attributes, void* isr)
{
    struct Idt* Idt = &idt_table[vector];
    Idt->isr_low = (uint32_t)isr & 0xFFFF;
    Idt->selector = 0x08;
    Idt->reserved = 0;
    Idt->type_attributes = 0x8E;
    Idt->isr_high = (uint32_t)isr >> 16 & 0xFFFF;
}

volatile uint32_t ticks = 0;

void zero_handler() {printk("DIVIDE BY ZERO ERROR");}
void pit_handler()
{
    char buf[256];
    ticks += 10;
    check_callouts(ticks);
    outb(0x20, 0x20);
}

void panic(const char* str)
{
    uint32_t eax, ecx, edx, ebx, esi, edi, esp;
    __asm__ volatile (
        "mov %%eax, %0\n\t"
        "mov %%ecx, %1\n\t"
        "mov %%edx, %2\n\t"
        "mov %%ebx, %3\n\t"
        "mov %%esi, %4\n\t"
        "mov %%edi, %5\n\t"
        "mov %%esp, %6\n\t"
        : "=m"(eax), "=m"(ecx), "=m"(edx), "=m"(ebx), "=m"(esi), "=m"(edi), "=m"(esp)
    );
    char buf[256];
    printk(str);
    printk("\n");
    itoa(eax, buf, 10);
    printk("EAX: ");
    printk(buf);
    printk("\n");
    itoa(ecx, buf, 10);
    printk("ECX: ");
    printk(buf);
    printk("\n");
    itoa(edx, buf, 10);
    printk("EDX: ");
    printk(buf);
    printk("\n");
    itoa(ebx, buf, 10);
    printk("EBX: ");
    printk(buf);
    printk("\n");
    itoa(esi, buf, 10);
    printk("ESI: ");
    printk(buf);
    printk("\n");
    itoa(edi, buf, 10);
    printk("EDI: ");
    printk(buf);
    printk("\n");
    itoa(esp, buf, 10);
    printk("ESP: ");
    printk(buf);
    printk("\n");
    while (1) {}
}

void keyboard_handler() {keyboard_handler_ext(); outb(0x20, 0x20);}
void syscall_handler() {printk("SYSCALL CALLED"); outb(0x20, 0x20);}
void overflow_handler() {panic("KERNEL PANIC: Overflow");}
void bounds_handler() {panic("KERNEL PANIC: Bounds exceed");}
void double_fault_handler() {panic("KERNEL PANIC: Double fault #DF");}
void general_protection_handler() {panic("KERNEL PANIC: General protection");}
void page_fault_handler() {panic("KERNEL PANIC: Page fault #PF");}
void coprocessor_error_handler() {panic("KERNEL PANIC: Coprocessor error");}

void IdtInstall()
{
    setIdtDescriptor(0, 0x8E, zero_handler);
    setIdtDescriptor(0x08, 0x8E, double_fault_handler);
    setIdtDescriptor(0x14, 0x8E, page_fault_handler);
    setIdtDescriptor(0x16, 0x8E, coprocessor_error_handler);
    setIdtDescriptor(0x20, 0x8E, pit_handler);
    setIdtDescriptor(0x21, 0x8E, keyboard_handler);
    setIdtDescriptor(0x80, 0x8F, syscall_handler);

    Idtr.limit = sizeof(idt_table) - 1;
    Idtr.base = (uint32_t)idt_table;

    __asm__ volatile ("lidt %0" :: "m"(Idtr));
}