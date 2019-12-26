#include "syscall.h"
// #include "../threads/system.h" causes error during compilation

#define MAX_STRING_SIZE 10 // the max string size is the size of the buffer that transports the String, we need it as we wanna test buffer overflow over the func


int main()
{
#if 1
    char * str = "Dtvrb3lwjeEf1kd2Z2rpXs0m56xHMGIo2b8lYMG6JwmktSYH6D1RxgtqmozbXIdSd45iNPMPIavgy1dqcMeEpuzuNaqWUsw3Ive6xuI\0";
    PutString(str, MAX_STRING_SIZE);    // Normal test
    PutString(str, MAX_STRING_SIZE*2);  // Buffer overflow test
    PutString(str, MAX_STRING_SIZE*50); // Will exceed the size of the string, but the function will stop cause of '\0'
#endif
    return 0;
}