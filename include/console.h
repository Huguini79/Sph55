#ifndef CONSOLE_H
#define CONSOLE_H

void ConsoleInstall();
void put_c(char c, int x, int y);
void printk(const char* str);
void kernel_panic();
void clear();

#endif