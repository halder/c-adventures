#include <stdio.h>
#include <stdlib.h>

/* Custom string length, excludes null terminator. */
size_t cstrlen(const char *str)
{
    size_t len = 0;
    
    while (*str != '\0') {
        len++;
        str++;
    }

    return len;
}

/* Custom string copy.
 * - determines length of string using `cstrlen`
 * - sets NULL terminator
 * - returns pointer to NULL terminator
 */
char *cstrcpy(char *dest, const char *source)
{
    size_t len = cstrlen(source);
    char *Nullterm = dest;
    
    for (size_t i = 0; i < len; i++) {
        *Nullterm = source[i];
        Nullterm++;
    }
    *Nullterm = '\0';

    return Nullterm;
}

// test functionality
int main(void)
{
    const char *str_as_ptr = "Hello"; // len = 5
    const char str_as_arr[] = {'W', 'o', 'r', 'l', 'd', '!'}; // len = 6
    char *str_ptr_heap;
    
    // buffer of size 8 on the heap
    if ((str_ptr_heap = malloc(sizeof(char) * 8)) == NULL) {
        printf("Error allocating memory block.");
        return 1;
    }

    char *ptr_to_nullterm = cstrcpy(str_ptr_heap, "Cabbage\0");

    if (((ptr_to_nullterm - 7) == str_ptr_heap) && (*ptr_to_nullterm == '\0')) {
        printf("`cstrcpy` works as intended.\n");
    }

    size_t len_of_ptr = cstrlen(str_as_ptr);
    size_t len_of_arr = cstrlen(str_as_arr);
    size_t len_ptr_heap = cstrlen(str_ptr_heap);
    
    printf("string %s has a length of %zu.\n", str_as_ptr, len_of_ptr);
    printf("string %s has a length of %zu.\n", str_as_arr, len_of_arr);
    printf("string %s has a length of %zu...\n", str_ptr_heap, len_ptr_heap);
    printf("...its length can also be calculated as: %zu.\n", (ptr_to_nullterm - str_ptr_heap));

    free(str_ptr_heap);
    
    return 0;
}
