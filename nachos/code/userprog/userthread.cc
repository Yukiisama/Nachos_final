#include "thread.h"
#include "userthread.h"
#include "system.h"
#ifdef CHANGED

userthread::userthread(){}

struct function_with_arg
{
    int f;
    int arg;
    int exit;
};

/**
* Init registers for the thread then run it
* Also activate the automatic terminaison
**/
static void StartUserThread(void *schmurtz){
    struct function_with_arg * s = (function_with_arg *) schmurtz;
    ASSERT(s!=NULL && s->f!=0 && s->arg!=0);
    //Init registers
    for (unsigned i = 0; i < NumTotalRegs; i++)
        machine->WriteRegister (i, 0);

    int TopOfStack = currentThread->space->AllocateUserStack(currentThread->getCaseThread());
      
    // Initial program counter -- must be location of Thread function
    machine->WriteRegister (PCReg, s->f);
    DEBUG ('x', "DEBUG: Function: %d\n", s->f);

    // Give the arg of the function in register r4
    machine->WriteRegister (4, s->arg);
    DEBUG ('x', "DEBUG: Arg: %d\n", s->arg);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
    DEBUG ('x', "DEBUG: NextPcReg: %d\n", machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister (StackReg, TopOfStack);
    DEBUG ('x', "DEBUG: TopOfStack: %d\n", TopOfStack);
   
    //Automatic Terminaison (thread_exit)
    machine->WriteRegister(RetAddrReg,s->exit); 
    
    machine->Run();
    
    delete s;
}
/**
* If possible create the thread , if not return -1
**/
int do_ThreadCreate(int f , int arg){
    if(currentThread->space->isThreadMapFull()){
      // Map Is Full
      return -1; 
    }
    int pos = currentThread->space->ThreadMap->Find();
    currentThread->setCaseThread(pos);
    currentThread->space->AddTo_NbThread(+1);

    Thread * new_thread = new Thread ("new_thread"); 
    struct function_with_arg * schmurtz = new struct function_with_arg();
    schmurtz->f = f; 
    schmurtz->arg = arg; 


    //We get the adresse of ThreadExit
    schmurtz->exit = machine->ReadRegister(6);
    //Finally start the thread
    new_thread->Start(StartUserThread,schmurtz);
    return 0;
}

/**
* Exit the current_thread
* Main is the last to exit
**/
void do_ThreadExit(){
  
  
  if (currentThread->space->GetNbThread() > 0){
    currentThread->space->AddTo_NbThread(-1);
    currentThread->space->ReleaseCase(currentThread->getCaseThread());
    
  }
  
  if(getNbProcess()>0 && currentThread->space->GetNbThread()<=0){
    decrementProcess();
  }
  if(currentThread->space->GetNbThread()<=0){
    currentThread->space->ReleaseMain();
    currentThread->space->ReleaseCase(0);
  }
  if(currentThread->space->GetNbThread() == 0 && getNbProcess()==0) 
    interrupt->Halt();
  else {
    currentThread->Finish();
  }
}
#endif // CHANGED
