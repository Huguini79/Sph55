#include "include/sched.h"
#include "include/console.h"
#include "include/mm.h"

struct callout callouts[64] = {0};
struct pcb processes_table[64] = {0};
struct pcb* current = &processes_table[0];
struct pcb* next = &processes_table[1];

void check_callouts(uint32_t ticks)
{
    for (int i = 0; i < 64; ++i)
    {
        if (callouts[i].ticks == ticks)
        {
            void (*function)(void) = (void (*)(void))callouts[i].callout_handler;
            function();
        }
    } 
}

void func()
{
    printk("Han pasado 3 segundos");
}

static int offset = -1;

void do_sleep(int s)
{
    offset++;
    callouts[offset].callout_handler = func;
    callouts[offset].ticks = s * 1000;
}

void yo()
{
    
}

struct pcb* createProcess(pid_t pid, uint32_t func)
{
    struct pcb* newProcess = &processes_table[pid];
    newProcess->pid = pid;
    newProcess->sigaction.sa_handler = 0;
    newProcess->sigaction.signal = 0;
    newProcess->alarm = 0;
    newProcess->uid = 0;
    newProcess->euid = 0;
    newProcess->gid = 0;
    newProcess->egid = 0;
    newProcess->tss.esp0 = 0x600000 + pid * 4096;
    newProcess->tss.ss0 = 0x10;
    newProcess->tss.eax = 0;
    newProcess->tss.ecx = 0;
    newProcess->tss.edx = 0;
    newProcess->tss.ebx = 0;
    newProcess->tss.eip = func;
    newProcess->tss.eflags = 0x202;
    newProcess->tss.cs = 0x08;
    newProcess->tss.ds = 0x10;
    newProcess->tss.es = 0x10;
    newProcess->tss.ss = 0x10;
    newProcess->tss.fs = 0x10;
    newProcess->tss.gs = 0x10;
    uint32_t* stack = (uint32_t*)0x3FF00 + pid * 8192; /* 8 KB of stack for each process */
    *stack = yo;
    newProcess->tss.esp = (uint32_t)stack;
    newProcess->tss.ebp = 0;
    newProcess->tss.iopb = 0x80000000;

    addTssDescriptor(newProcess);

    return newProcess;
}

void yield()
{
    if (next != NULL)
    {
        current = next;
        if (&processes_table[current->pid].tss.eip != NULL)
        {
            next = &processes_table[current->pid+1];
        }
        if (current->tss.eip != NULL)
        {
            switch_to(current);

        } else
        {
            current = &processes_table[1];
            if (current->tss.eip != NULL)
            {
                switch_to(current);
            }
        }
    }
}

pid_t getCurrentPID()
{
    return current->pid;
}

void copyProcess(struct pcb* dest, struct pcb* origin)
{
    dest->pid = origin->pid;
    dest->father = origin->father;
    dest->alarm = origin->alarm;
    
    dest->sigaction.sa_handler = origin->sigaction.sa_handler;
    dest->sigaction.signal = origin->sigaction.signal;
    
    dest->uid = origin->uid;
    dest->euid = origin->euid;
    dest->gid = origin->gid;
    dest->egid = origin->egid;

    dest->tss.eax = origin->tss.eax;
    dest->tss.ecx = origin->tss.ecx;
    dest->tss.edx = origin->tss.edx;
    dest->tss.ebx = origin->tss.ebx;
    dest->tss.edi = origin->tss.edi;
    dest->tss.esi = origin->tss.esi;
    dest->tss.esp = origin->tss.esp;
    dest->tss.ebp = origin->tss.ebp;
    dest->tss.eip = origin->tss.eip;
}

void switch_to(struct pcb* pcb)
{
    if (pcb != NULL)
    {
        current = &processes_table[pcb->pid];
        copyProcess(current, pcb);
        uint16_t tss_selector = (current->pid + 3) * 8;
        volatile struct
        {
            uint32_t offset;
            uint16_t selector;

        } __attribute__((packed)) _tmp;

        _tmp.offset = 0;
        _tmp.selector = tss_selector;

        __asm__ volatile ("ljmp %0" :: "m"(_tmp));

    }
}

void switch_current()
{
    switch_to(current);
}