#include "syscall.h"

void print(char c, int n)
{
    int i;
#if 1
    for (i = 0; i < n; i++) {
        PutChar(c + i);
    }
    PutChar('\n');
#endif
}
int main()
{
    print('a',10);   // Will put from 'a' to a+9
    print('A',62); // Will put from 'A' to 'z+62'
    return 8;        // the return value we wanted to catch following the questions of the course
}
