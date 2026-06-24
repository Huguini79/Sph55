#ifndef MM_H
#define MM_H

#include <stdint.h>
#include <stddef.h>

void init_paging();
void enablePaging();
void loadPageDirectory();

#endif