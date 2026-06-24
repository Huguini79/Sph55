#include "include/sched.h"

#include <stdint.h>
#include <stddef.h>

struct Gdt
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t flags;
    uint8_t base_high;

} __attribute__((packed));

struct Gdtr
{
    uint16_t limit;
    uint32_t base;

} __attribute__((packed));

struct Gdtr Gdtr;

struct Gdt gdt_table[8192] __attribute__((aligned(8)));

void setGdtDescriptor(
    int n,
    uint16_t limit,
    uint16_t base_low,
    uint8_t base_mid,
    uint8_t access_byte,
    uint8_t flags,
    uint8_t base_high
)
{
    struct Gdt* Gdt = &gdt_table[n];
    Gdt->limit = limit;
    Gdt->base_low = base_low;
    Gdt->base_mid = base_mid;
    Gdt->access_byte = access_byte;
    Gdt->flags = flags;
    Gdt->base_high = base_high;
}

void GdtInstall()
{
    setGdtDescriptor(0, 0, 0, 0, 0, 0, 0);
    setGdtDescriptor(1, 0xFFFF, 0, 0, 0x9B, 0xCF, 0);
    setGdtDescriptor(2, 0xFFFF, 0, 0, 0x93, 0xCF, 0);
    struct tss tss;
    tss.esp0 = 0x600000;
    tss.ss0 = 0x10;
    uint32_t tss_address = (uint32_t)&tss;
    setGdtDescriptor(3, sizeof(tss), tss_address & 0xFFFF, (tss_address >> 16) & 0xFF, 0x89, 0x40, (tss_address >> 24) & 0xFF);

    Gdtr.limit = sizeof(gdt_table) - 1;
    Gdtr.base = (uint32_t)gdt_table;

    __asm__ volatile ("lgdt %0" :: "m"(Gdtr));
}