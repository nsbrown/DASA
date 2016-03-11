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

void power(struct commandData* words, int arg)
{
	
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
	
	for(i = 0; words[i].word != 0 ;i++)
	{
		char * result = fgets(buffer, BUFFER_SIZE, input);
		if (result == NULL) {
			if(!feof(input)) {
				perror("fgets returned null");
			}
			else {break;}
			continue;
		}
		if(strcasecmp(buffer, words[i].word) == 0)
		{
			(*words[i].fp)(words[i].nextArray, arg);
			return;
		}
	}
	printf("word %s not found\n", buffer);
}


//--------------High Level Array-------------------
struct commandData highLevel[] =
{
	{"ON\n", power, 0 , 1}, {"OFF\n", power, 0, 0},
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
//--------------High Level Secondary Array--------
//struct commandData highLevelSec[] =
//{
//	{"A"}, {""},
//	{}, {},
//	{}, {},
//	{}, {},
//};

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
	
	//sleep(500);
	printf("RUNNING COMMAND SCRIPT");

	for(;;)
	{
		processNextWord(dasaNames, 0);
		
	}
	return EXIT_SUCCESS;
}



