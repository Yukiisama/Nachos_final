#include "synch.h"
#include "usersemaphore.h"
#include "copyright.h"

#ifdef CHANGED
static Semaphore *ListSemaphore[MAX_SEMAPHORE];
/**
* Available Semaphore return the indice of an available semaphore .
* Return -1 if full
**/
int availableSemaphore(){
    for(int i = 0 ; i<MAX_SEMAPHORE;i++)
    {
        if(ListSemaphore[i]==0)
            return i;
    }
    return -1;
}

/**
* Init the semaphore for the user with the value : value, return -1 if no semaphore available .
* Return the semaphore id
**/
int Semaphore_Init(int value){
    int id = availableSemaphore();
    if(id==-1){
        printf("Max Semaphore reached ,delete some semaphore");
        return -1;
    }
    ListSemaphore[id]= new Semaphore("Semaphore number " + id, value);
    return id;
}
/**
* Use the semaphore->P function on the id semaphore
* Return the semaphore id
**/
int Semaphore_P(int id){
    if(id==-1) return id;
    ListSemaphore[id]->P();
    return id;
}
/**
* Use the semaphore->V function on the id semaphore
* Return the semaphore id
**/
int Semaphore_V(int id){
    if(id==-1) return id;
    ListSemaphore[id]->V();
    return id;
}

#endif // CHANGED