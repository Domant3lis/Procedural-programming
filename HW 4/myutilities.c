#include <string.h>
#include "myutilities.h"
// Gets a number `num` raise by a power of `n`
int pow_int32(short num, unsigned short n)
{
    int rez = (0 == n) ? 1 : num;
    for (unsigned short iter = 1; iter < n; ++iter){
        rez *= num;    
    }

    return rez;
}

// Fills 
void do_spacing_with(char *str, char fill, short fill_till)
{
    fill_till -= strlen(str);
    char *str_ptr = str + strlen(str);
    while (--fill_till > 0)
    {
        // printf("%d '%c'\n", fill_num, str_ptr);
        *(str_ptr++) = fill;
    }
    *str_ptr = 0;
}
