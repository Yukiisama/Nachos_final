#ifdef CHANGED

#include "copyright.h"

#include "system.h"

#include "synchconsole.h"

#include "synch.h"

#include <limits.h>

static Semaphore *readAvail;
static Semaphore *writeDone;
static Lock * ReadMutex;
static Lock * WriteMutex;
static Semaphore * StringS;

static void ReadAvailHandler(void *arg) {
  (void)arg;
  readAvail->V();
}
static void WriteDoneHandler(void *arg) {
  (void)arg;
  writeDone->V();
}

SynchConsole::SynchConsole(const char *in, const char *out) {
  readAvail  = new Semaphore("read avail", 0);
  writeDone  = new Semaphore("write done", 0);
  ReadMutex  = new Lock("ReadMutex");
  WriteMutex = new Lock("WriteMutex");
  StringS    = new Semaphore("string", 1);
  console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole()

{

  delete console;

  delete writeDone;

  delete readAvail;

  delete ReadMutex;

  delete WriteMutex;

  delete StringS;
}
/*
@brief SynchPutchar's goal is to put a single char into the console .
@param ch the caracter to put .
*/
void SynchConsole::SynchPutChar(int ch){
  WriteMutex->Acquire();
  console->PutChar(ch);
  writeDone->P(); // wait for write to finish
  WriteMutex->Release();
}
/*
@brief SynchGetchar's goal is to get a single char from the console .
@return the caracter from the console 
*/
int SynchConsole::SynchGetChar()
{
  ReadMutex->Acquire();
  readAvail->P(); // wait for character to arrive
  char ch = console->GetChar();
  ReadMutex->Release();
  if(ch==EOF) return (int) '\0';
  return (int) ch;
}
/*
@brief SynchPutString's goal is to put a single string to the console .
@param the string to put. 
*/
void SynchConsole::SynchPutString(const char s[])

{
    StringS->P();
    unsigned int i = 0;
    while(s[i]!='\0'){
	  SynchPutChar(s[i]);
      i++;
    }
    StringS->V();
}
/*
@brief SynchGetString's goal is to get a single string from the console .
Stops whenever the maximal size is reached , or encounter a special character \n or \0
@param where to get the string .
@param the maximal size of the string 
*/
void SynchConsole::SynchGetString(char *s, int n) {
  StringS->P();
  int i = 0;
  char c;
  while(i<n && (c=SynchGetChar())!='\0' && c!='\n')
  {
	  s[i]=c;
	  i++;
  }
  s[i]='\0';
  StringS->V();
}
/*
@brief SynchPutInt's goal is to put a single int to the console .
@param the int to put. 
*/
void SynchConsole::SynchPutInt(int n){
    //Integer Max size , +1 cause a terminating null character is automatically appended after the content written.
    int size = snprintf(NULL, 0, "%d",INT_MIN) + 1; 
    char * string = new char[size];
    snprintf(string,size,"%d",n);
    SynchPutString(string);
    delete [] string;
}
/*
@brief SynchGetInt's goal is to get a single int to the console .
@param the pointer to write the int we get. 
*/
void SynchConsole::SynchGetInt(int * n){
    int * i = new int;
    int size = snprintf(NULL, 0, "%d",INT_MIN) + 1;
    char * str = new char[size];
    SynchGetString(str,size-1); // size-1 to leave space for the '\0'
    sscanf(str,"%d",i);
    machine->WriteMem(*n,sizeof(int),*i);
    delete [] str;
    delete i;
}
#endif // CHANGED

#ifdef CHANGED
/*
@brief copyStringFromMachine 's goal is to transform a Pointer Mips in pointer Linux .
@param from is the adress of the MIPS string
@param to is the adress of the Linux String
@param size is the max_size of the string
* 
*/
int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size){
    int value = 0;
    unsigned int i = 0;
    while(i<size && machine->ReadMem(from+i, 1, &value)){
        to[i]= (char) value;
        if(to[i]=='\0') return -1;
        i+=1;
    }
    to[size]='\0';
    return 0;
}

/*
@brief copyStringToMachine 's goal is to transform a Pointer Linux in pointer Mips .
@param to is the adress of the Linux String
@param from is the adress of the MIPS string
@param size is the max_size of the string
* 
*/
int SynchConsole::copyStringToMachine(int to , char * from , unsigned size){
    unsigned i = 0;
    while(i< size && from[i]!='\0'){
        machine->WriteMem(to + i , 1 , from[i]);
        i++;
    }
    machine->WriteMem(to + i , 1 , '\0');
    if (i < size) return -1; // in case we encountered a special char
    else return 0; // otherwise

}
#endif // CHANGED