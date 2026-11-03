#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int     age;
    char    name[6]; // VLA; has to be last member of the struct
} foo ;

int main(void)
{   
    foo *bar;
    foo snax;
    foo *ptr_bar, *snxptr;
    
    snax.age = 2;
    snax.name[3] = 0;
    //snax.name = {'s', 'i', 'x', '\0'};
    memcpy(snax.name, "six", 4);
    snxptr = &snax;

    printf("snax age: %d\n", snxptr->age);

    bar = malloc(sizeof(foo) + (sizeof(char) * 6));  // allocate space for a name of length 5 (+ \0 terminator)
    
    //printf("bar.name is at %ld and has a size of %lu\n", (long)&bar->name, sizeof(bar));

    bar->age = 99;
    strcpy(bar->name, "five5"); // all is well;

    ptr_bar = bar;

    printf("first element of bar: %d\n", *ptr_bar);


    //(ptr_bar[5] == '\0') ? printf("value of *bar.name[5]: '\\0'\n"): printf("value of *bar.name[5]: %c\n", ptr_bar[5]);

    free(bar);
    
    return 0;
}
