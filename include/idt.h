#ifndef IDT_H
#define IDT_H

#include <stdbool.h>

void pit_handler_stub();
void IdtInstall();

extern bool multitasking_init;

#endif