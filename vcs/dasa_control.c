#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
char address[] = {"nathanbrown@10.0.0.58"};
int currentTemp = 75;
int currentPosition_x = 0;
int currentPosition_y = 0;
int currentPosition_z = 0;

struct commandData
{
		char* word;
		void (*fp)(struct commandData*, int);
		struct commandData* nextArray;
		int arg;
};

void toDasaDemo(char* string, int arg)
{
	char str[BUFFER_SIZE];
	sprintf(str, "ssh -i id_rsa %s \"./dasademo %s %d\"", address, string, arg);
	system(str);
}

void toDasaDemostr(char *string, char*secondString)
{
	char str[BUFFER_SIZE];
	sprintf(str, "ssh -i id_rsa %s \"./dasademo %s %s\"", address, string, secondString);
	system(str);
}
void mode(struct commandData* words, int arg)
{
	switch(arg)
	{
		case 0:
				//system("./dasademo SHOWER");
				toDasaDemostr("MODE", "SHOWER");
				break;
		case 1:
				//system("./dasademo RAIN");
				toDasaDemostr("MODE", "RAIN");
				break;
		case 2:
				//system("./dasademo MASSAGE");
				toDasaDemostr("MODE", "MASSAGE");
				break;
		case 3:
				//system("./dasademo JET");
				toDasaDemostr("MODE", "JET");
				break;
		default:
				printf("error");
	}

}
void tempUp(struct commandData* words, int arg)
{
	if((currentTemp + arg) < 75 || (currentTemp + arg) > 120)
	{
		printf("Unasafe Temperature");
	}
	else
	{
		currentTemp = currentTemp + arg;
		printf("Turning temp up");
		toDasaDemo("temp", currentTemp);
	}
	//toDasaDemo("temp", arg);
}
void tempDown(struct commandData* words, int arg)
{
	if((currentTemp - arg) < 75 || (currentTemp - arg) > 120)
	{
		printf("Unasafe Temperature");
	}
	else
	{
		currentTemp = currentTemp - arg;
		printf("Turning temp up");
		toDasaDemo("temp", currentTemp);
	}
}
void moveBackwards(struct commandData* words, int arg)
{
	if ((currentPosition_z - arg) < 0 || (currentPosition_z - arg) > 100)
	{
		printf("Invalid z positon %d", (currentPosition_z - arg));
	}
	else
	{
		currentPosition_z = currentPosition_z - arg;
		printf("Moving backwards\n");
		toDasaDemo("z", currentPosition_z);
	}
}
void moveForward(struct commandData* words, int arg)
{
	if ((currentPosition_z + arg) < 0 || (currentPosition_z + arg) > 100)
	{
		printf("Invalid z positon %d", (currentPosition_z + arg));
	}
	else
	{
		currentPosition_z = currentPosition_z + arg;
		printf("Moving forwards\n");
		toDasaDemo("z", currentPosition_z);
	}
}
void moveLeft(struct commandData* words, int arg)
{
	if ((currentPosition_x - arg) < -50 || (currentPosition_x - arg) > 50)
	{
		printf("Invalid x positon %d", (currentPosition_x - arg));
	}
	else
	{
		currentPosition_x = currentPosition_x - arg;
		printf("Moving left\n");
		toDasaDemo("x", currentPosition_x);
	}
}
void moveRight(struct commandData* words, int arg)
{
	if ((currentPosition_x + arg) < -50 || (currentPosition_x + arg) > 50)
	{
		printf("Invalid x positon %d", (currentPosition_x + arg));
	}
	else
	{
		currentPosition_x = currentPosition_x + arg;
		printf("Moving right\n");
		toDasaDemo("x", currentPosition_x);
	}
}

void moveDown(struct commandData* words, int arg)
{
	if ((currentPosition_y + arg) < 0 || (currentPosition_y + arg) > 100)
	{
		printf("Invalid y positon %d", (currentPosition_y + arg));
	}
	else
	{
		currentPosition_y = currentPosition_y + arg;
		printf("Moving down\n");
		toDasaDemo("y", currentPosition_y);
	}
}

void moveUp(struct commandData* words, int arg)
{
	if ((currentPosition_y - arg) < 0 || (currentPosition_y - arg) > 100)
	{
		printf("Invalid y positon %d", (currentPosition_y - arg));
	}
	else
	{
		currentPosition_y = currentPosition_y - arg;
		printf("Moving up\n");
		toDasaDemo("y", currentPosition_y);
	}
}

void power(struct commandData* words, int arg)
{
	printf("in power function: arg = %d \n", arg);
	if(arg == 1)
	{
		printf("TURNING ON\n");
		//system("./dasademo ON");
		toDasaDemo("ON", -1);
	}
	else if(arg == 0)
	{
		printf("TURNING OFF\n");
		//system("./dasademo OFF");
		toDasaDemo("OFF", -1);
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

struct commandData headMode [] =
{
	{"SHOWER", mode, 0, 0}, {"RAIN", mode, 0, 1},
	{"MASSAGE", mode, 0, 2}, {"JET", mode, 0, 3},
	{0,0,0,0}

};
struct commandData showerHeadMode [] =
{
	{"MODE", processNextWord, headMode, 0}, {"SHOWER", mode, 0, 0}, {"RAIN", mode, 0, 1}, 
	{"MASSAGE", mode, 0, 2}, {"JET", mode, 0, 3}, {0,0,0,0}

};
//-------------Temp Small Incremental-------------------
struct commandData tempSmallInc[] =
{
	{"UP", tempUp, 0, 3}, {"DOWN", tempDown, 0, 3}, {"COOLER", tempDown, 0, 3},
	{"COLDER", tempDown, 0, 3}, {"WARMER", tempUp, 0, 3}, {"HOTTER", tempUp, 0, 3},
	{0,0,0,0}

};
//--------------Temp Higher Additional------------------
struct commandData tempLargeInc[] =
{
	{"UP", tempUp, 0, 7}, {"DOWN", tempDown, 0, 7}, {"COOLER", tempDown, 0, 7},
	{"COLDER", tempDown, 0, 7}, {"WARMER", tempUp, 0, 7}, {"HOTTER", tempUp, 0, 7},
	{0,0,0,0}
};
//--------------Temp Filler Array-----------------------
struct commandData tempFiller[] =
{
	{"LITTLE", processNextWord, tempSmallInc, 0}, {"LOT", processNextWord, tempLargeInc, 0},
	{0,0,0,0}

};
//-------------Temp Array-------------------------
struct commandData tempArray[] =
{
	{"UP", tempUp, 0, 5}, {"DOWN", tempDown, 0, 5}, {"WARMER", tempUp, 0, 5},
	{"HOTTER", tempUp, 0, 5}, {"COOLER", tempDown, 0, 5}, {"COLDER", tempDown, 0, 5},
	{"A", processNextWord, tempFiller, 0}, {0,0,0,0}
};
//-------------Small Incremental-------------------
struct commandData smallInc[] =
{
	{"UP", moveUp, 0, 5}, {"DOWN", moveDown, 0, 5}, {"RIGHT", moveRight, 0, 5},
	{"LEFT", moveLeft, 0, 5}, {"FORWARD", moveForward, 0, 5}, {"BACKWARDS", moveBackwards, 0, 5},
	{"HIGHER", moveUp, 0, 5}, {"LOWER", moveDown, 0, 5}, {0,0,0,0}

};
//--------------Higher Additional------------------
struct commandData largeInc[] = 
{
	{"UP", moveUp, 0, 15}, {"DOWN", moveDown, 0, 15}, {"RIGHT", moveRight, 0, 15},
	{"LEFT", moveLeft, 0, 15}, {"FORWARD", moveForward, 0, 15}, {"BACKWARDS", moveBackwards, 0, 15},
	{"HIGHER", moveUp, 0, 15}, {"LOWER", moveDown, 0, 15}, {0,0,0,0}
};
//--------------Filler Array-----------------------
struct commandData fillerArray[] =
{
	{"LITTLE", processNextWord, smallInc, 0}, {"LOT", processNextWord, largeInc, 0},
	{0,0,0,0}

};
//--------------Move Array-------------------------
struct commandData moveArray[] =
{
	{"A", processNextWord, fillerArray, 0}, {"UP", moveUp, 0, 10}, {"SLIGHTLY", processNextWord, smallInc, 0},
	{"DOWN", moveDown, 0, 10}, {"RIGHT", moveRight, 0, 10}, {"LEFT", moveLeft, 0, 10}, 
	{"FORWARD", moveForward, 0, 10},{"BACKWARDS", moveBackwards, 0, 10}, {"MUCH", processNextWord, largeInc, 0},
	{0,0,0,0}
};

//--------------High Level Array-------------------
struct commandData highLevel[] =
{
	{"ON", power, 0 , 1}, {"OFF", power, 0, 0}, {"FORWARD", moveForward, 0, 10}, {"BACKWARDS",moveBackwards, 0, 10},
	{"LEFT", moveLeft, 0, 10}, {"RIGHT", moveRight, 0, 10}, {"UP", moveUp, 0, 10}, 
	{"DOWN", moveDown, 0, 10}, {"MOVE", processNextWord, moveArray, 0}, {"A", processNextWord, fillerArray, 0},
	{"SLIGHTLY", processNextWord, smallInc, 0}, {"MUCH", processNextWord, largeInc, 0},

	{"TEMP", processNextWord, tempArray, 0}, {"TEMPERATURE", processNextWord, tempArray, 0}, {"WARMER", tempUp, 0, 5},
	{"HOTTER", tempUp, 0, 5}, {"COOLER", tempDown, 0, 5}, {"COLDER", tempDown, 0, 5},

	{"MODE", processNextWord, headMode, 0}, {"SHOWER", mode, 0, 0}, {"RAIN", mode, 0, 1}, 
	{"MASSAGE", mode, 0, 2}, {"JET", mode, 0, 3},
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



