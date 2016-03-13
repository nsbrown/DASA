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

void tempDown(struct commandData* words, int arg)
{
	printf("Turning temp down");
	system("./dasademo temp 75");
}
void tempUp(struct commandData* words, int arg)
{
	printf("Turning temp up");
	system("./dasademo temp 80");
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
//--------------Temperature Array-----------------
struct commandData tempArray [] =
{
	{"UP", tempUp, 0, 5}, {"DOWN", tempDown, 0, -5}, {0,0,0,0}
};

//--------------Mid Level Secondary Array---------
struct commandData midLevel[] =
{
	{"UP", moveUp, 0, 10}, {"DOWN", moveDown, 0, -10}, {"RIGHT", moveRight, 0, 10}, 
	{"LEFT", moveLeft, 0, -10},  
	{0,0,0,0}
//	{"A"}, {""},
//	{}, {},
//	{}, {},
//	{}, {},
};

//--------------High Level Array-------------------
struct commandData highLevel[] =
{
	{"ON", power, 0 , 1}, {"OFF", power, 0, 0}, {"MOVE", processNextWord, midLevel, 0},
	{"TEMPERATURE", processNextWord, tempArray, 0}, {"TEMP", processNextWord, tempArray, 0},
	{0,0,0,0}
	//{"Move", processNextWord(), }, {"Up", processNextWord(),   },
	//{"Down", processNextWord(), }, {"Right", processNextWord(),  },
	//{"Left"}, {"Motion"},
	//{"Manuever"}, {"Forward"},
	//{"Back"}, {"Backwards"},
	//{"Temp"}, {"Temperature"},
	//{"Hotter"}, {"Warmer"},
	//{"Colder"}, {"Cooler"},
	//{"Cool"}, {"Heat"},
	
};

//--------------Name Array-------------------------
struct commandData dasaNames[] = 
{	//{"Daisy",proccessNextWord(),highLevel}, 
	//{"Donald" proccessNextWord(), highLevel},
	{"DASA", processNextWord, highLevel, 0}, 
	{0,0,0,0}
};



//--------------


int main()
{
	
	printf("RUNNING COMMAND SCRIPT\n");

	for(;;)
	{
		processNextWord(dasaNames, 0);
		
	}
	return EXIT_SUCCESS;
}



