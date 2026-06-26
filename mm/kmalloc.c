#include <stdint.h>
#include <stddef.h>

#define HEAP_SIZE 104857600
#define BLOCK_SIZE 4096
#define TOTAL_BLOCKS (HEAP_SIZE / BLOCK_SIZE)

uint32_t bitmap[TOTAL_BLOCKS];

uint32_t searchForFree()
{
    
}