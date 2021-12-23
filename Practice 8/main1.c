// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long *createArray(size_t size, long low, long high);
long randNum(long low, long high);

int main()
{
    size_t size = 100;
    long *array = createArray(size, 10, 20);

    printf("ARRAY: \n");
    for (size_t i = 0; i < size; ++i)
        printf("%ld ", array[i]);

    free(array);

    return 0;
}

long randNum(long low, long high)
{ 
    return low + (rand() % (high - low + 1));
}

// creates an array, whose size is `size`
// with random numbers ranging from `low` to `high` (both inclusive)
// and return a pointer to it
//
// NULL is returned if failure to allocate memory for the array occurs 
// if `low` is higher `high`, then no array is created and NULL is returned
// IMPORTANT: this array must be free()'d after use
long *createArray(size_t size, long low, long high)
{
    // checks if rng boundaries are correct
    if (high < low)
        return NULL;
    
    long *array = calloc(size, sizeof(long));
    if(!array)
        return NULL;

    // fills an array with random values
    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < size; ++i)
        *(array + i) = randNum(low, high); 

    return array;
}
