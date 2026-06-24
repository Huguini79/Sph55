#include "include/string.h"
#include "include/console.h"
#include "include/io.h"

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_FONT 0x0F

uint16_t* framebuffer;
int x = 0;
int y = 0;

void put_c(char c, int x, int y)
{
    framebuffer[(y * VGA_WIDTH) + x] = DEFAULT_FONT << 8 | c;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (insb(0x3D5) & 0xC0) | cursor_start);
    
    outb(0x3D4, 0x0B);
    outb(0x3D5, (insb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
    uint16_t pos = (y * VGA_WIDTH) + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void ConsoleInstall()
{
    framebuffer = (uint16_t*)0xB8000;
    enable_cursor(0, 15);
    clear();
}

void scroll()
{
    for (int i = VGA_WIDTH * 3; i < VGA_HEIGHT * VGA_WIDTH; ++i)
    {
        framebuffer[i] = framebuffer[i + VGA_WIDTH];
    }

    for (int i2 = (VGA_HEIGHT - 1) * VGA_WIDTH - 2; i2 < VGA_WIDTH * VGA_HEIGHT; ++i2)
    {
        framebuffer[i2] = 0x0F << 8 | ' ';
    }

    for (int i = VGA_WIDTH * 3 + VGA_WIDTH - 1; i < VGA_HEIGHT * VGA_WIDTH; i += VGA_WIDTH)
    {
        framebuffer[i] = 0x0F << 8 | '|';
    }

}

void printk(const char* str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i)
    {
        if (x >= VGA_WIDTH)
        {
            y++;
            x = 0;
        }

        if (y >= VGA_HEIGHT)
        {
            scroll();
            y = 24;
            x = 0;
        }
        
        if (str[i] == '\n')
        {
            y++;
            x = 0;
            update_cursor(x, y);
        
        } else
        {
            put_c(str[i], x, y);
            x++;
            update_cursor(x, y);
        }
    }

}

void clear()
{
    x = 0;
    y = 0;

    for (int i = 0; i < VGA_HEIGHT; ++i)
    {
        for (int ii = 0; ii < VGA_WIDTH; ++ii)
        {
            put_c(' ', ii, i);
        }
    }

    for (int i = VGA_WIDTH * 3 + VGA_WIDTH - 1; i < VGA_HEIGHT * VGA_WIDTH; i += VGA_WIDTH)
    {
        framebuffer[i] = 0x0F << 8 | '|';
    }

    printk("Welcome to SPH55 Operating System from Scratch\n\n");
    for (int i = 0; i < 80; ++i)
    {
        printk("-");
    }


}