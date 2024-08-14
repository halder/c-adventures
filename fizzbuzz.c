#include <stdio.h>
#include <string.h>

int read_user_input(char *buffer, int *n)
{
    printf("Enter an integer between 1 and 100: ");
    // load user input into buffer
    fgets(buffer, sizeof buffer, stdin);
    // strip '\n' from buffer
    buffer[strcspn(buffer, "\n")] = 0;
    // return sscanf result for flow of control
    return sscanf(buffer, "%d", n);
}

void flush_stdin()
{
    int c;
    // grab and discard all characters until a newline (including) is encountered
    while ((c = getchar()) != '\n' && c != EOF);
}

void flush_str_buffer(char *str, int str_len)
{
    for (int i = 0; i < str_len; i++) {
        str[i] = 0;
    }
}

#define MAX_STR_LEN 9

void fizz_buzz(int n)
{
    int i, i_str = 0;
    char str[MAX_STR_LEN] = "";

    for ( i = 1; i < n+1; i++) {
        // reset buffer
        i_str = 0;
        flush_str_buffer(str, MAX_STR_LEN);

        if ((i % 3) == 0) {
            str[i_str++] = 'F';
            str[i_str++] = 'i';
            str[i_str++] = 'z';
            str[i_str++] = 'z';
        }
        if ((i % 5) == 0) {
            str[i_str++] = 'B';
            str[i_str++] = 'u';
            str[i_str++] = 'z';
            str[i_str++] = 'z';
        }
        if (i_str == 0) {
            snprintf(str, MAX_STR_LEN, "%d", i);
        }
        printf("%s, ", str);
    }
    printf("\n");
}

int main(void)
{
    char buffer[10] = ""; // holds 9 characters + '\0' (implicitly)
    int ctrl, n;

    while (1) {
        ctrl = read_user_input(buffer, &n);
        
        if (ctrl != 1) {
            printf("Please enter a valid integer!\n");
            printf("-------\n");
            flush_stdin();
            continue;
        }
        
        if ((n < 1) || (n > 100)) {
            printf("Input must be between 1 and 100!\n");
        } else {
            fizz_buzz(n);
        }

        printf("-------\n");

        // flush stdin to avoid overflow into next loop cycle
        // eg: "1234567890" -> "0\n"
        // not sure why max buffer == 1234567 ; shouldn't it hold 9 chars??
        flush_stdin();
    }
    
    return 0;
}
