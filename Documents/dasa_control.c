
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <delay.h>

#define BUFFER_SIZE 256
//FILE *input;

int main(int argc, char **argv)

{
	FILE *input;
	//input = stdin;
	char *buffer;
	buffer = (char *)malloc(BUFFER_SIZE);


	if(argc > 1)
	{
		if(!strcmp(argv[1], "-"))
		{
			input = stdin;
		}
		else
		{
			input = fopen(argv[1], "r");
			if(NULL == input)
			{
				printf("Unable to open");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		input = stdin;
	}
	sleep(500);

	for(;;)
	{
		fgets(buffer, BUFFER_SIZE, input);

		if(strcmp(buffer, "DASA ON") == 0)
		{
			printf("TURNING ON");
			free(buffer);
		}
		else if(strcmp(buffer, "DASA OFF") == 0)
		{
			printf("TURNING OFF");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA STOP") == 0)
		{
			printf("STOPPING CURRENT ACTION");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA RESET") == 0)
		{
			printf("RESETTING");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA BACK") == 0)
		{
			printf("MOVING AWAY");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA FORWARD") == 0)
		{
			printf("MOVING FORWARD");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA LEFT") == 0)
		{
			printf("MOVING LEFT");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA RIGHT") == 0)
		{
			printf("MOVING RIGHT");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA DOWN") == 0)
		{
			printf("MOVING DOWN");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA UP") == 0)
		{
			printf("MOVING UP");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA MODE SHOWER") == 0)
		{
			printf("CHANGING TO SHOWR MODE");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA MODE JET") == 0)
		{
			printf("CHANGING TO JET MODE");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA MODE MASSAGE") == 0)
		{
			printf("CHANGING TO MASSAGE MODE");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA MODE RAIN") == 0)
		{
			printf("CHANGING TO RAIN MODE");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA TEMPERATURE LOWER") == 0)
		{
			printf("LOWERING TEMPERATURE");
			free(buffer);

		}
		else if(strcmp(buffer, "DASA TEMPERATURE HIGHER") == 0)
		{
			printf("INCREASING TEMPERATURE");
			free(buffer);

		}
		else
		{
			printf("failure to recognize, try again");
			free(buffer);
		}

	}
	return EXIT_SUCCESS;


}




