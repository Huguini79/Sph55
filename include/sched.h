#ifndef SCHED_H
#define SCHED_H

#include "include/signal.h"

#include <stdint.h>
#include <stddef.h>

typedef uint32_t pid_t;
typedef uint32_t time_t;

struct callout
{
    void* callout_handler;
    uint32_t ticks;
};

extern struct callout callouts[64];

struct tss
{
    uint32_t link;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldtr;
    uint32_t iopb;

} __attribute__((packed));

struct pcb
{
    pid_t pid;
    pid_t father;
    uint32_t priority;
    uint32_t counter;
    struct sigaction sigaction;
    uint32_t alarm;
    uint32_t exit_code;
    uint16_t uid, euid, gid, egid;
    time_t time;
    struct tss tss;
    // uint32_t eax, ecx, edx, ebx, esi, edi, ebp, esp, eip;
};

extern struct pcb processes_table[64];
extern struct pcb* current;

void check_callouts(uint32_t ticks);
void do_sleep(int s);
struct pcb* createProcess(pid_t pid, uint32_t func);
void yield();
void switch_to(struct pcb* pcb);
void switch_current();

#endif