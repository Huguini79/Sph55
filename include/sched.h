#ifndef SCHED_H
#define SCHED_H

extern int pid_t;
extern int time_t;

struct callout
{
    void* callout_handler;
    uint32_t ticks;
};

struct pcb
{
    pid_t pid;
    time_t time;
};

#endif