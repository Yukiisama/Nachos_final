#include "userfork.h"
#include "thread.h"
#include "addrspace.h"
#include "synch.h"
#include "system.h"
#include "openfile.h"
#include "synchconsole.h"
#include "userthread.h"
#ifdef CHANGED
struct give_addrspace{
    AddrSpace * addrspace;
};

static void forkExec_start(void * schmurtz){
    give_addrspace * addrspace = (give_addrspace *) schmurtz;
    currentThread->space = addrspace->addrspace;
    currentThread->space->InitRegisters();
    currentThread->space->RestoreState();
    machine->Run();

}
int do_forkExec(){
    //We get the filename from machine
	unsigned maxNameSize = 1024;
	int from = machine->ReadRegister(4);
	char * fileName = new char[maxNameSize];
	synchConsole->copyStringFromMachine(from,fileName,maxNameSize);
	//We init the main thread
	Thread * threadNoyau = new Thread("ThreadNoyauProcess");
    //We get the executable
    OpenFile * executable = fileSystem->Open(fileName);
    //Time to init the addrspace then give it to the struct
    AddrSpace * addrspace = new AddrSpace(executable);
    give_addrspace * s = new give_addrspace;
    s->addrspace = addrspace;
    //delete executable and Start forkExec_start with the given addrspace 
    threadNoyau->Start(forkExec_start,s);
    //We update the current nb process
    addProcess();
    delete executable;
    return 0;
}

#endif // CHANGED
