#include "syscall.h"
// #include "../threads/system.h" causes error during compilation

#define MAX_STRING_SIZE 10 // the max string size is the size of the buffer that transports the String, we need it as we wanna test buffer overflow over the func

int main()
{
#if 1
    int size = MAX_STRING_SIZE*100;
	char str[size];
	GetString(str,size);                     // Normal test
	PutString(str,size);
#endif
    return 0;
}
