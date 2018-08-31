#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int ac, char *av[]){
	if ( ac != 3){
		printf("too few arguments\n");
		exit(1);
	}
	int retVal = rename(av[1],av[2]);
	printf("retval %d\n",retVal);
	return 0;
}
