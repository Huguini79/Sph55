#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str)
{
    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;

}

int strcmp(const char* str1, const char* str2)
{
    unsigned char u1, u2;
    while (1)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if (u1 != u2)
        {
            return u1 - u2;
        }

        if (u1 == '\0')
        {
            break;
        }
    }

    return 0;
}