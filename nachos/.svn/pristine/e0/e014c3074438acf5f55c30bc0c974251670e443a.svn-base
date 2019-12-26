#include "syscall.h"

void f(void * c){
  PutChar((char)c);
  PutChar('\n');
  //ThreadExit(); No need with automatic terminaison
}

void g(void * c){
  PutString((char *)c,50);
  //ThreadExit(); No need with automatic terminaison
}

int main(){
  volatile int i = 0;
  PutString("Lancement des tests\n",50);
  
  ThreadCreate(f,'A');
  ThreadCreate(f,'B');
  ThreadCreate(f,'C');
  for (i = 0;i<40;i++){
    //If thread can't be created ThreadCreate return -1 cause of not enough space , we don't print a message for this
    //Cause it would flood too much, not the point of the test .
    ThreadCreate(f,'A');
  }
  for (i = 0;i<40;i++){
    ThreadCreate(g,"TEST-1-");
    ThreadCreate(g,"TEST-2-");
  }
  PutChar('\n');
  }
 

 
