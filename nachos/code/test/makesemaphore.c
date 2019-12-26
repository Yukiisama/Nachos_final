#include "syscall.h"
static sem_t Prod_Sem; 
static sem_t Cons_Sem;
static sem_t Mutex_Sem;
int nb = 0;

void consommateur(void * c)
{

	Semaphore_P(Prod_Sem);
	Semaphore_P(Mutex_Sem);
	GetChar();
	Semaphore_V(Mutex_Sem);
	Semaphore_V(Cons_Sem);

}

void producteur(void * c)
{

	Semaphore_P(Cons_Sem);
	Semaphore_P(Mutex_Sem);
	PutChar(c);
	Semaphore_V(Mutex_Sem);
	Semaphore_V(Prod_Sem);
}



int main(){
  Prod_Sem  = Semaphore_Init(1);
  Cons_Sem = Semaphore_Init(1);
  Mutex_Sem = Semaphore_Init(1);
  ThreadCreate(producteur,'B');
  ThreadCreate(producteur,'C');
  ThreadCreate(consommateur,' ');
  
  return 0;
  }






