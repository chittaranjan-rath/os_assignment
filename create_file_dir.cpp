#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include	<pwd.h>
#include	<grp.h>
#include        <string.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include        <string>
using namespace std;
void make_a_new_file(const char * filename,const char * path);
void make_a_new_dir(const char * dirname,const char * path);
void make_a_new_file(const char * filename,const char * path){
	printf("file to be created is %s at path %s \n",filename,path);
	if(!strcmp(path,".")){
		int fd_for_w = open(filename, O_RDWR | O_CREAT , 0700);
		printf("file descriptor fd_for_w = %d\n",fd_for_w);
		if(fd_for_w == -1){
			//printf ("error number %d\n", errno);
			perror("program");
		}
		printf("file opened \n");
		int close_id = close (fd_for_w);
		if(close_id < 0){
			printf("erroe while closeoing\n");
			perror("c1");
			exit(1);
		}
		printf("file closed \n");
	}
	else{
		int chdirval= chdir(path);
		printf("chdir returned val is %d\n",chdirval);
		int fd_for_w = open(filename, O_RDWR | O_CREAT , 0700);
		printf("file descriptor fd_for_w = %d\n",fd_for_w);
		if(fd_for_w == -1){
			//printf ("error number %d\n", errno);
			perror("program");
		}
		printf("file opened \n");
		int close_id = close (fd_for_w);
		if(close_id < 0){
			printf("erroe while closeoing\n");
			perror("c1");
			exit(1);
		}
		printf("file closed \n");
	}
}
void make_a_new_dir(const char * dirname,const char * path){
	printf("dir to be created is %s at path %s \n",dirname,path);
	if(!strcmp(path,".")){
		if (mkdir(dirname,0777) == -1) {
        	//perror(argv[0]);
        	exit(EXIT_FAILURE);
		printf("failed to make dir\n");
   	}
	}
	else{
		int chdirval= chdir(path);
		printf("chdir returned val is %d\n",chdirval);
		if (mkdir(dirname,0777) == -1) {
        	//perror(argv[0]);
        	exit(EXIT_FAILURE);
		printf("failed to make dir\n");
	}
	}
}
int main(int ac, char *av[]){
	if ( ac == 4){
		char command[100];
		strcpy(command,av[1]);
		if(!strcmp(command,"create_file")){
			make_a_new_file(av[2],av[3]);
		}
		else if(!strcmp(command,"create_dir")){
			make_a_new_dir(av[2],av[3]);
		}
		else{
			printf("wrong command\n");
			exit(1);
		}
	}
	else{
		printf("too few arguments\n");
		exit(1);
	}
	return 0;
}
