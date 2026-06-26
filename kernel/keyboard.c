#include <stdint.h>
#include <stddef.h>

#include "include/console.h"
#include "include/io.h"
#include "include/string.h"
#include "include/sched.h"

char keyboard_buffer[12312];
uint8_t scancode;

int pos = 0;

struct pcb* newProcess;
struct pcb* newProc;

void addCharacter(char c)
{
    keyboard_buffer[pos++] = c;
    keyboard_buffer[pos] = '\0';
}

void funct2()
{
    printk("\nTASK2: Second process in execution");
    switch_to(newProcess);
    printk("\nTASK2: I'm back");
    switch_to(newProcess);
}

void funct()
{
    printk("\nTASK1: Hello World!");
    // newProc = createProcess(2, (uint32_t)funct2);
    // yield();
}

void keyboard_handler_ext()
{
    scancode = insb(0x60);
    if (scancode == 0x1E) {printk("a"); addCharacter('a');}
    if (scancode == 0x30) {printk("b"); addCharacter('b');}
    if (scancode == 0x2E) {printk("c"); addCharacter('c');}
    if (scancode == 0x20) {printk("d"); addCharacter('d');}
    if (scancode == 0x12) {printk("e"); addCharacter('e');}
    if (scancode == 0x21) {printk("f"); addCharacter('f');}
    if (scancode == 0x22) {printk("g"); addCharacter('g');}
    if (scancode == 0x23) {printk("h"); addCharacter('h');}
    if (scancode == 0x17) {printk("i"); addCharacter('i');}
    if (scancode == 0x24) {printk("j"); addCharacter('j');}
    if (scancode == 0x25) {printk("k"); addCharacter('k');}
    if (scancode == 0x26) {printk("l"); addCharacter('l');}
    if (scancode == 0x32) {printk("m"); addCharacter('m');}
    if (scancode == 0x31) {printk("n"); addCharacter('n');}
    if (scancode == 0x18) {printk("o"); addCharacter('o');}
    if (scancode == 0x19) {printk("p"); addCharacter('p');}
    if (scancode == 0x10) {printk("q"); addCharacter('q');}
    if (scancode == 0x13) {printk("r"); addCharacter('r');}
    if (scancode == 0x1F) {printk("s"); addCharacter('s');}
    if (scancode == 0x14) {printk("t"); addCharacter('t');}
    if (scancode == 0x16) {printk("u"); addCharacter('u');}
    if (scancode == 0x2F) {printk("v"); addCharacter('v');}
    if (scancode == 0x11) {printk("w"); addCharacter('w');}
    if (scancode == 0x2D) {printk("x"); addCharacter('x');}
    if (scancode == 0x15) {printk("y"); addCharacter('y');}
    if (scancode == 0x2C) {printk("z"); addCharacter('z');}

    if (scancode == 0x39) {printk(" "); addCharacter(' ');}

    if (scancode == 0x1A) {printk("["); addCharacter('[');}
    if (scancode == 0x1B) {printk("]"); addCharacter(']');}
    if (scancode == 0x0D) {printk("="); addCharacter('=');}
    if (scancode == 0x28) {printk("'"); addCharacter('"');}
    if (scancode == 0x29) {printk("`"); addCharacter('`');}
    if (scancode == 0x0C) {printk("-"); addCharacter('-');}
    if (scancode == 0x34) {printk("."); addCharacter('.');}
    if (scancode == 0x33) {printk(","); addCharacter(',');}
    if (scancode == 0x35) {printk("/"); addCharacter('/');}
    if (scancode == 0x27) {printk(";"); addCharacter(';');}
    if (scancode == 0x0F) {printk("     "); addCharacter(' ');}

    if (scancode == 0x1C)
    {
        if (strcmp(keyboard_buffer, "clear") == 0)
        {
            clear();

        }

        else if (strcmp(keyboard_buffer, "help") == 0)
        {
            printk("\nclear                                 help\nloadprocess                           exec\nyield\n");
        }
        
        else if (strcmp(keyboard_buffer, "loadprocess") == 0)
        {
            newProcess = createProcess(1, (uint32_t)funct);
            printk("\n");
            // switch_to(newProcess);

        }

        else if (strcmp(keyboard_buffer, "yield") == 0)
        {
            yield();
        }

        else if (strcmp(keyboard_buffer, "exec") == 0)
        {
            if (current->tss.eip != NULL)
                switch_current();
            else
                printk("\nPLEASE LOAD A PROCESS AT FIRST\n");
        }

        else if (strcmp(keyboard_buffer, "") == 0)
        {
            printk("\n");
        }
        
        else
        {
            printk("\n");
            printk(keyboard_buffer);
            printk(": not found\n");
        }
        printk("# ");
        pos = 0;
        keyboard_buffer[pos] = '\0';
    }
}