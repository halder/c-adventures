/* a and i _usually_ are pushed in row on the stack, e.g.:
 * |----a-----|i|
 * |----------|-|
 * 
 * the for-loop will run out of bounds of `a` by incrementing `i`
 * one over (11) the declared length of `a` (10).
 * 
 * the 10th loop will therefore set a[10], which (likely, depending on compiler)
 * corresponds to the address of `i`, to 0.
 * 
 * this program crashes on clang v15.0.0, Ventura v13.6.8.
 */
   
int main(void)
{
    int a[10], i;

    for(i = 0; i < 11; i++) {
        a[i] = 0;
    }
}
