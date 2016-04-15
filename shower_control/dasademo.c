#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "dgs.h"

#define NO_CHANGE -99999

DasaServerInfo * requestState;

int processPositionCommand(int argc,char ** argv);

int doPositionCommand(int x,int y,int z);
int doOnCommand(void);
int doShutdown(void);
int doOffCommand(void);
int doModeCommand(int mode);
int doTempCommand(int temp);

int main(int argc,char ** argv)
{
    int shmid = shmget(SHARED_KEY, sizeof(DasaServerInfo), 0666);
    if (shmid  < 0) {
        perror("dasademo shmget");
        return -1;
    }

    /*
     * Now we attach the segment to our data space.
     */
     requestState = shmat(shmid, NULL, 0);
    if (requestState  == (DasaServerInfo *) -1) {
        perror("dasademo shmat");
        return -2;
    }

  if (argc < 2)
    {
      fprintf(stderr,"No argument given to DASA\n");
      exit(3);
    }

  if (strcasecmp(argv[1],"x") == 0 || strcasecmp(argv[1],"y") == 0 || strcasecmp(argv[1],"z") == 0)
    return processPositionCommand(argc,argv);
  if (strcasecmp(argv[1],"on") == 0)
    return doOnCommand();
  if (strcasecmp(argv[1],"shutdown") == 0)
    return doShutdown();
  if (strcasecmp(argv[1],"off") == 0)
    return doOffCommand();
  if (strcasecmp(argv[1],"mode") == 0)
    {
       if (argc < 3)
         {
           fprintf(stderr,"No mode given for MODE command\n");
           exit(3);
         }
       if (strcasecmp(argv[2],"shower") == 0)
         return doModeCommand(SHOWER);
       if (strcasecmp(argv[2],"jet") == 0)
         return doModeCommand(JET);
       if (strcasecmp(argv[2],"rain") == 0)
         return doModeCommand(RAIN);
       if (strcasecmp(argv[2],"massage") == 0)
         return doModeCommand(MASSAGE);
       fprintf(stderr,"Unknown mode %s given for MODE command\n",argv[2]);
       exit(3);
     }
  if (strcasecmp(argv[1],"temp") == 0)
    {
       if (argc < 3)
         {
           fprintf(stderr,"No temperature given for TEMP command\n");
           return -1;
         }
      int temp = atoi(argv[2]);
      return doTempCommand(temp);
     }
  fprintf(stderr,"Unknown command %s given to DASA\n",argv[1]);
  exit(3);
}

int doShutdown()
{
  requestState->shutdown = 1;
  return 0;
}

int processPositionCommand(int argc,char ** argv)
{
  int x = NO_CHANGE;
  int y = NO_CHANGE;
  int z = NO_CHANGE;
  int i;
  for (i = 1; i < argc; i+= 2)
     {
       if (strcasecmp(argv[i],"x") == 0)
         x = atoi(argv[i+1]);
       else if (strcasecmp(argv[i],"y") == 0)
         y = atoi(argv[i+1]);
       else if (strcasecmp(argv[i],"z") == 0)
         z = atoi(argv[i+1]);
       else
         {
            fprintf(stderr,"Unknown position argument %s to DASA\n",argv[i]);
            return -1;
         }
     }
  return doPositionCommand(x,y,z);
}

int doPositionCommand(int x,int y,int z)
{
  if (x != NO_CHANGE)
    {
      if (x < -50 || x > 50)
        {
          fprintf(stderr,"Invalid x position %d\n",x);
          return -1;
        }
      requestState->xPos = x;
    }
  if (y != NO_CHANGE)
    {
      if (y < 0 || y > 100)
        {
          fprintf(stderr,"Invalid y position %d\n",y);
          return -1;
        }
      requestState->yPos = y;
    }
  if (z != NO_CHANGE)
    {
      if (z < 0 || z > 100)
        {
          fprintf(stderr,"Invalid y position %d\n",z);
          return -1;
        }
      requestState->zPos = z;
    }
    return 0;
}
   
int doOnCommand(void)
{
  requestState->onOff = ON;
  return 0;
}

int doOffCommand(void)
{
  requestState->onOff = OFF;
  return 0;
}

int doModeCommand(int mode)
{
  switch (mode)
    {
      case JET:
      case RAIN:
      case MASSAGE:
      case SHOWER:
        requestState->mode = mode;
        break;
      default:
        fprintf(stderr,"Unknown mode value %d\n",mode);
     }
  return 0;
}

int doTempCommand(int temp)
{
  if (temp < 75 || temp > 110)
    {
      fprintf(stderr,"Unsafe temperature %d given to DASA temperature\n",temp);
      return -1;
    }
  requestState->temp = temp;
  return 0;
}

    
