#include "include/mm.h"

#include <stdint.h>
#include <stddef.h>

#define TOTAL_PAGE_DIRECTORY_ENTRIES 1024
#define TOTAL_PAGE_TABLE_ENTRIES 1024

uint32_t page_directory[TOTAL_PAGE_DIRECTORY_ENTRIES] __attribute__((aligned(4096)));
uint32_t first_page_table[TOTAL_PAGE_TABLE_ENTRIES] __attribute__((aligned(4096)));
uint32_t second_page_table[TOTAL_PAGE_TABLE_ENTRIES] __attribute__((aligned(4096)));

void init_paging()
{   
        /* Present */
        /* Supervisor level */
        /* Read/Write */
    uint32_t attributes = (1 << 0) | (1 << 1);
    
    /* Fill the tables */
    for (int i = 0; i < TOTAL_PAGE_DIRECTORY_ENTRIES; ++i)
    {
        /* Read/Write avaible (bit 1) */
        /* Not present (bit 0) */
        page_directory[i] = 0x0;
    }

    for (int i = 0; i < TOTAL_PAGE_TABLE_ENTRIES; ++i)
    {
        /* Present */
        /* Supervisor level */
        /* Read/Write */
        first_page_table[i] = (i * 4096) | attributes;
    }

    for (int i = 0; i < TOTAL_PAGE_TABLE_ENTRIES; ++i)
    {
        /* Present */
        /* Supervisor level */
        /* Read/Write */
        second_page_table[i] = (0x400000 + (i * 4096)) | attributes;
    }

    /* MAP ONLY THE FIRST 4 MB FOR THE MOMENT */
    page_directory[0] = ((uint32_t)first_page_table) | attributes;
    page_directory[1] = ((uint32_t)second_page_table) | attributes;

    uint32_t phys_dir = (uint32_t)&page_directory[0];

    loadPageDirectory();

}