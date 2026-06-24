#ifndef GDT_H
#define GDT_H

#include "include/sched.h"

#include <stdint.h>
#include <stddef.h>

void GdtInstall();
void clearBitBusy(uint16_t selector);
void addTssDescriptor(struct pcb* pcb);

#endif