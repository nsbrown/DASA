#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "dgs.h"

extern void dasaDisplay(int argc,char ** argv);


DasaServerInfo * requestedState = 0;

DasaServerInfo currentState = {0,0};

static void resetState(DasaServerInfo * state);
static int checkForChanges();

int main(int argc,char ** argv,char ** envp)
{
   int shid = shmget(SHARED_KEY,sizeof(DasaServerInfo),IPC_CREAT | 0666);
   if (shid < 0)
     {
       perror("failed to get shid");
       return -1;
     }
    requestedState = shmat(shid,0,0);
    if (requestedState == NULL || (int)requestedState == -1)
      {
        perror("attaching shared memory");
        return -2;
      }
    
    resetState(&currentState);
    resetState(requestedState);
    
    dasaDisplay(argc,argv);
    shmdt(requestedState);
    return 0;
}


static void resetState(DasaServerInfo * state)
{
    state->shutdown = 0;
    state->onOff = OFF;
    state->temp = 70;
    state->mode = SHOWER;
    state->xPos = 0;
    state->yPos = 0;
    state->zPos = 0;
}

