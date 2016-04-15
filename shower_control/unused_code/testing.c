#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
void sprint(char* string, int arg)
{
	char str[32];
	sprintf(str, "./dasademo %s %d", string, arg);
	printf("the new string is %s: ", str);
}
int main()
{
	
	printf("RUNNING\n");
	int num = 32;
	sprint("temp", num);
	
	return EXIT_SUCCESS;
}