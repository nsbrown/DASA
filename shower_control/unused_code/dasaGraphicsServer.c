#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "dgs.h"


DasaServerInfo * requestedState;

static DasaServerInfo currentState;

static void resetState(DasaServerInfo * state);
static void processRequests(void);
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
    
    processRequests();
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

static void processRequests(void)
{
  while (1)
    {
      if (requestedState->shutdown)
         return;
      int sltime = checkForChanges();
      usleep(sltime);
    }
}

#define MOVE_TIME_PER_POINT 20000
#define MOVE_TIME_PER_DEGREE 50000

static int checkForChanges(void)
{
  int minSleep = 0;
  int maxSleep = 100000;
  
  if (requestedState->xPos != currentState.xPos)
    {
      if (requestedState->xPos < currentState.xPos)
        currentState.xPos--;
      else
        currentState.xPos++;
      printf("Moving x to %d\n",currentState.xPos);
      if (minSleep < MOVE_TIME_PER_POINT)
        minSleep = MOVE_TIME_PER_POINT;
    }
  if (requestedState->yPos != currentState.yPos)
    {
      if (requestedState->yPos < currentState.yPos)
        currentState.yPos--;
      else
        currentState.yPos++;
      printf("Moving y to %d\n",currentState.yPos);
      if (minSleep < MOVE_TIME_PER_POINT)
        minSleep = MOVE_TIME_PER_POINT;
    }
    if (requestedState->zPos != currentState.zPos)
    {
      if (requestedState->zPos < currentState.zPos)
        currentState.zPos--;
      else
        currentState.zPos++;
      printf("Moving z to %d\n",currentState.zPos);
      if (minSleep < MOVE_TIME_PER_POINT)
        minSleep = MOVE_TIME_PER_POINT;
    }
  if (requestedState->temp != currentState.temp)
    {
      if (requestedState->temp < currentState.temp)
        currentState.temp--;
      else
        currentState.temp++;
      printf("Moving temp to %d\n",currentState.temp);
      if (minSleep < MOVE_TIME_PER_DEGREE)
        minSleep = MOVE_TIME_PER_DEGREE;
    }
  if (requestedState->onOff != currentState.onOff)
    {
      currentState.onOff = requestedState->onOff;
      if (currentState.onOff == ON)
        printf("Turning water ON\n");
      else
        printf("Turning water OFF\n");
    }
  if (requestedState->mode != currentState.mode)
    {
      currentState.mode = requestedState->mode;
      switch (currentState.mode)
        {
        case SHOWER:
           printf("setting mode to SHOWER\n");
           break;
        case JET:
           printf("setting mode to JET\n");
           break;
        case RAIN:
           printf("setting mode to RAIN\n");
           break;
        case MASSAGE:
           printf("setting mode to MASSAGE\n");
           break;
        }
    }
  if (minSleep == 0)
    return maxSleep;
  return minSleep;
}

