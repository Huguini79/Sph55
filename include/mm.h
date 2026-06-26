#ifndef MM_H
#define MM_H

#include <stdint.h>
#include <stddef.h>

void init_paging();
void enablePaging();
void loadPageDirectory(uint32_t page_directory);

extern uint32_t phys_dir;

#endif