#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define SHOWER 1
#define JET 2
#define RAIN 3
#define MASSAGE 4

#define NO_CHANGE -99999

int processPositionCommand(int argc,char ** argv);

int doPositionCommand(int x,int y,int z);
int doOnCommand(void);
int doOffCommand(void);
int doModeCommand(int mode);
int doTempCommand(int temp);

int main(int argc,char ** argv)
{
  if (argc < 2)
    {
      fprintf(stderr,"No argument given to DASA\n");
      return -1;
    }

  if (strcasecmp(argv[1],"x") == 0 || strcasecmp(argv[1],"y") == 0 || strcasecmp(argv[1],"z") == 0)
    return processPositionCommand(argc,argv);
  if (strcasecmp(argv[1],"on") == 0)
    return doOnCommand();
  if (strcasecmp(argv[1],"off") == 0)
    return doOffCommand();
  if (strcasecmp(argv[1],"mode") == 0)
    {
       if (argc < 3)
         {
           fprintf(stderr,"No mode given for MODE command\n");
           return -1;
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
       return -1;
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
  return -1;
}


int processPositionCommand(int argc,char ** argv)
{
  int x = NO_CHANGE;
  int y = NO_CHANGE;
  int z = NO_CHANGE;
  for (int i = 1; i < argc; i+= 2)
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
      printf("Moving X to %d\n",x);
    }
  if (y != NO_CHANGE)
    {
      if (y < 0 || y > 100)
        {
          fprintf(stderr,"Invalid y position %d\n",y);
          return -1;
        }
      printf("Moving Y to %d\n",y);
    }
  if (z != NO_CHANGE)
    {
      if (z < 0 || z > 100)
        {
          fprintf(stderr,"Invalid y position %d\n",z);
          return -1;
        }
      printf("Moving Z to %d\n",z);
    }
    return 0;
}
   
int doOnCommand(void)
{
  printf("Doing ON command\n");
  return 0;
}

int doOffCommand(void)
{
  printf("Doing OFF command\n");
  return 0;
}

int doModeCommand(int mode)
{
  switch (mode)
    {
      case JET:
        printf("Doing MODE JET command\n");
        break;
      case RAIN:
        printf("Doing MODE RAIN command\n");
        break;
      case MASSAGE:
        printf("Doing MODE MASSAGE command\n");
        break;
      case SHOWER:
        printf("Doing MODE SHOWER command\n");
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
  printf("Doing TEMP %d command\n",temp);
  return 0;
}

    