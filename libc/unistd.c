#include "include/sched.h"

#include <stdint.h>
#include <stddef.h>

void sleep(int s)
{
    do_sleep(s);
}