
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
	input = stdin;
	char *buffer;
	buffer = (char *)malloc(BUFFER_SIZE);
	//sleep(500);
	printf("RUNNING COMMAND SCRIPT");

	for(;;)
	{
		char * result = fgets(buffer, BUFFER_SIZE, input);
		if (result == NULL) {
			if(!feof(input)) {
				perror("fgets returned null");
			}
			else {break;}
			continue;
		}
		if(strcmp(buffer, "DASA ON\n") == 0)
		{
			printf("TURNING ON\n");
			system("./dasademo ON");
		}
		else if(strcmp(buffer, "DASA OFF\n") == 0)
		{
			printf("TURNING OFF\n");
			system("./dasademo OFF");
		}
		else if(strcmp(buffer, "DASA STOP\n") == 0)
		{
			printf("STOPPING CURRENT ACTION\n");

		}
		else if(strcmp(buffer, "DASA RESET\n") == 0)
		{
			printf("RESETTING\n");

		}
		else if(strcmp(buffer, "DASA BACK\n") == 0)
		{
			printf("MOVING AWAY\n");

		}
		else if(strcmp(buffer, "DASA FORWARD\n") == 0)
		{
			printf("MOVING FORWARD\n");

		}
		else if(strcmp(buffer, "DASA LEFT\n") == 0)
		{
			printf("MOVING LEFT\n");
			system("./dasademo x 10");

		}
		else if(strcmp(buffer, "DASA RIGHT\n") == 0)
		{
			printf("MOVING RIGHT\n");
			system("./dasademo x 10");

		}
		else if(strcmp(buffer, "DASA DOWN\n") == 0)
		{
			printf("MOVING DOWN\n");
			system("./dasademo y 10");

		}
		else if(strcmp(buffer, "DASA UP\n") == 0)
		{
			printf("MOVING UP\n");
			system("./dasademo y 10");

		}
		else if(strcmp(buffer, "DASA MODE SHOWER\n") == 0)
		{
			printf("CHANGING TO SHOWR MODE\n");
			system("./dasademo SHOWER");

		}
		else if(strcmp(buffer, "DASA MODE JET\n") == 0)
		{
			printf("CHANGING TO JET MODE\n");
			system("./dasademo JET");

		}
		else if(strcmp(buffer, "DASA MODE MASSAGE\n") == 0)
		{
			printf("CHANGING TO MASSAGE MODE\n");
			system("./dasademo MASSAGE");

		}
		else if(strcmp(buffer, "DASA MODE RAIN\n") == 0)
		{
			printf("CHANGING TO RAIN MODE\n");
			system("./dasademo RAIN");

		}
		else if(strcmp(buffer, "DASA TEMPERATURE LOWER\n") == 0)
		{
			printf("LOWERING TEMPERATURE\n");

		}
		else if(strcmp(buffer, "DASA TEMPERATURE HIGHER\n") == 0)
		{
			printf("INCREASING TEMPERATURE\n");

		}
		else
		{
			printf("failure to recognize, %s try again\n", buffer);
			
		}

	}
	return EXIT_SUCCESS;
}




