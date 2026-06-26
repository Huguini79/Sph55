#include "include/mm.h"

#include <stdint.h>
#include <stddef.h>

#define TOTAL_PAGE_DIRECTORY_ENTRIES 1024
#define TOTAL_PAGE_TABLE_ENTRIES 1024

uint32_t page_directory[TOTAL_PAGE_DIRECTORY_ENTRIES] __attribute__((aligned(4096)));
uint32_t page_tables[TOTAL_PAGE_DIRECTORY_ENTRIES][TOTAL_PAGE_TABLE_ENTRIES] __attribute__((aligned(4096)));

uint32_t phys_dir;

void init_paging()
{   
        /* Present */
        /* Supervisor */
        /* Read/Write */
    uint32_t flags = (1 << 0) | (1 << 2) | (1 << 1);
    
    uint32_t offset = 0;

    for (int i = 0; i < TOTAL_PAGE_DIRECTORY_ENTRIES; ++i)
    {
        uint32_t *entry = page_tables[i];
        for (int j = 0; j < TOTAL_PAGE_TABLE_ENTRIES; ++j)
        {
            entry[j] = (offset + (j * 4096)) | flags;
        }
        offset += (TOTAL_PAGE_DIRECTORY_ENTRIES * 4096);
        page_directory[i] = (uint32_t)entry | flags;
    }
    
    phys_dir = (uint32_t)page_directory;

    loadPageDirectory(phys_dir);

}