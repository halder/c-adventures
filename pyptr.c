/* Uncovering C pointers of python struct copying mechanisms.
 * Python lists under the hood.
 * 
 * The following Python code is equivalent to this C program:
 * 
 * ======================== Python 3.10 ===========================
 * 
 * a = [1, 2, 3, 4, 5]
 * b = a
 * b[1] = -99
 * print(a)
 * >> [1, -99, 3, 4, 5]
 * 
 * ================================================================
 * 
 * `b` is merely a pointer to `a`.
 * The same is true for all(?) Python (non-atomic) objects as well.
 */

#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    int *p;

    p = a;

    p[1] = -99;

    for (int i = 0; i < 5; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }

    return 0;
}
