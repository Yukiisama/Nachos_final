#include "syscall.h"
#include <limits.h>

int main()
{
#if 1
    PutInt(INT_MIN);     // Will output the minimum int
    PutChar('\n');
    PutInt(INT_MIN - 1); // Underflow test : Will output the maximum int
    PutChar('\n');
    PutInt(INT_MAX);     // Will output the maximum int
    PutChar('\n');
    PutInt(INT_MAX + 1); // Overflow test : Will output the minimum int
    PutChar('\n');
    PutInt('a');         // Will output the ASCII code for 'a' (97)
    PutChar('\n');
    PutInt('b');         // Will output the ASCII code for 'b' (98)
    PutChar('\n');
    PutInt('c');         // Will output the ASCII code for 'c' (99)
    PutChar('\n');
#endif
    return 0;
}
