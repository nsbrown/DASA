#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

char address[] = {"nathanbrown@155.42.107.130"};

int main()
{
	printf("Running test...\n");
	
	char str[32];
	sprintf(str, "ssh %s \"echo I am working\"", address);
	system(str);
	
	return EXIT_SUCCESS;
}
