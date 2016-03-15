#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

struct commandData 
{
		char* word;
		void (*fp)(struct commandData*, int);
		struct commandData* nextArray;	
		int arg;
};

void aLittleUp(struct commandData* words, int arg)
{
	printf("Moving a little up\n");
	system("./dasademo y 5");
}

void moveBackwards(struct commandData* words, int arg)
{
	printf("Moving backwards\n");
	system("./dasademo z -10");
}
void moveForward(struct commandData* words, int arg)
{
	printf("Moving forward\n");
	system("./dasademo z 10");
}
void moveLeft(struct commandData* words, int arg)
{
	printf("Moving shower head left\n");
	system("./dasademo x -10");
}
void moveRight(struct commandData* words, int arg)
{
	printf("Moving shower head right\n");
	system("./dasademo x 10");
}

void moveDown(struct commandData* words, int arg)
{
	printf("Moving shower head down\n");
	system("./dasademo -10");
}

void moveUp(struct commandData* words, int arg)
{
	printf("Moving the shower head up\n");
	system("./dasademo y 10");
}

void power(struct commandData* words, int arg)
{
	printf("in power function: arg = %d \n", arg);
	if(arg == 1)
	{
		printf("TURNING ON\n");
		system("./dasademo ON");
	}
	else if(arg == 0)
	{
		printf("TURNING OFF\n");
		system("./dasademo OFF");
	}
}

void processNextWord(struct commandData* words, int arg)
{
	FILE *input;
	input = stdin;
	char buffer[BUFFER_SIZE];
	int i;
	
	if (fscanf(input, "%s", buffer) == 0) {
			printf("Got end of input\n");
			if(!feof(input)) {
				perror("returned null");
			}
			return;
		}
		//printf("read %s \n", buffer);
		
	for(i = 0; words[i].word != 0 ;i++)
	{
		printf("comparing buffer %s to %s \n", buffer, words[i].word);
		if(strcasecmp(buffer, words[i].word) == 0)
		{
			(*words[i].fp)(words[i].nextArray, words[i].arg);
			return;
		}
	}
	printf("%s not found\n", buffer);
}

//--------------Mid Level Secondary Array---------
struct commandData midLevel[] =
{
	{"UP", moveUp, 0, 10}, {"DOWN", moveDown, 0, -10}, {"RIGHT", moveRight, 0, 10}, 
	{"LEFT", moveLeft, 0, -10}, {0,0,0,0}
//	{"A"}, {""},
//	{}, {},
//	{}, {},
//	{}, {},
};
struct commandData increment[] =
{
	{"UP", aLittleUp, 0, 5}, {0,0,0,0}

};
//--------------Higher Additional------------------
struct commandData higherAdd[] = 
{
	{"LITTLE", processNextWord, increment, 0}, {"LOT", processNextWord, increment, 0}, {0,0,0,0}
};
//--------------High Level Array-------------------
struct commandData highLevel[] =
{
	{"ON", power, 0 , 1}, {"OFF", power, 0, 0}, {"FORWARD", moveForward, 0, 10}, {"BACKWARDS",moveBackwards, 0, -10},
	{"MOVE", processNextWord, midLevel, 0},
	{"A", processNextWord, higherAdd, 0}, {"MUCH", processNextWord, higherAdd, 0},
	{0,0,0,0}
};

//--------------Name Array-------------------------
struct commandData dasaNames[] = 
{	
	{"DASA", processNextWord, highLevel, 0}, 
	{"DONALD", processNextWord, highLevel, 0},
	{"DAISY", processNextWord, highLevel, 0},
	{0,0,0,0}
};


int main()
{
	
	printf("RUNNING COMMAND SCRIPT\n");

	for(;;)
	{
		processNextWord(dasaNames, 0);
		
	}
	return EXIT_SUCCESS;
}




