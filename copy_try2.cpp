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
void SearchDirectory( char *name , char tardir[] ,char *currentWorkingDir);
void copy_file( char *filename, char *dirname , char * to_append);
int main(int ac, char *av[]){
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
     		 perror("getcwd() error");
        else
      		printf("current working directory is: %s\n", cwd);
	char tPath[256];char spath[256];
	if ( ac == 3){
		//strcpy(spath,cwd);
		//strcpy(tPath,cwd);
		strcpy(tPath,"/");
		strcat(tPath,av[2]);
		//strcat(tPath,"/");
		//strcat(spath,"/");
		strcat(spath,av[1]);
		//strcat(spath,"/");
		printf("spath is %s \ntpath is = %s\n",spath,tPath);
		SearchDirectory( spath, tPath,cwd);
	}
	return 0;
}


void SearchDirectory(char *spath , char *tardir ,char *currentWorkingDir) {
    DIR *dir = opendir(spath);  	              //Assuming absolute pathname here.
    if(dir) {
	printf("dir name here is %s \n",spath);
	printf("tardir name here is %s \n",tardir);
	char *dirname = (char *)tardir;
	int chdirval = chdir(dirname);
	printf("chdir returned val is %d\n",chdirval);
	printf("for chdir dirname name here is %s \n",dirname);
	if (mkdir(spath,0777) == -1) {
        	//perror(argv[0]);
        	exit(EXIT_FAILURE);
		printf("failed to make dir\n");
   	}
	chdirval = chdir(currentWorkingDir);
	printf("chdir returned val is %d\n",chdirval);
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
     		 perror("getcwd() error");
        else
      		printf("current working directory is: %s\n", cwd);
		
	/*strcat(tardir,"/"); 
	strcat(tardir,spath);
	printf("tardir name here is %s \n",tardir);*/
	char *tardir1;
	tardir1 = tardir;
	printf("tardir11111 name here is %s \n",tardir1);
        char Path[256], *EndPtr = Path;
        struct dirent *e;
        strcpy(Path, spath); 
	strcat(Path,"/");                 //Copies the current path to the 'Path' variable.
        EndPtr += strlen(Path);              //Moves the EndPtr to the ending position.
        while((e = readdir(dir)) != NULL  ) { 
		chdirval = chdir(currentWorkingDir);
		printf("chdir returned val is %d\n",chdirval);	
		printf("tardir inside while name here is %s \n",tardir);		 //Iterates through the entire directory.
            struct stat info;                //Helps us know about stuff	
	  if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;
            strcpy(EndPtr, e->d_name);       //Copies the current filename to the end of the path, overwriting it with each loop.
		printf("e->d_name %s \n" ,e->d_name);
		printf("path is %s\n",Path);
		printf("stat val =%d\n",stat(Path, &info));
            if(!stat(Path, &info)) {         //stat returns zero on success.
                if(S_ISDIR(info.st_mode) && e->d_name!="." && e->d_name!="..") {  //Are we dealing with a directory?
                    //Make corresponding directory in the target folder here.
                    	printf("rec call with path =%s tardir =%s\n",Path,tardir);

			SearchDirectory(Path,tardir,currentWorkingDir);   //Calls this function AGAIN, this time with the sub-name.
                } else if(S_ISREG(info.st_mode)) { //Or did we find a regular file?
                    //Run Copy routine
			printf("fname is = %s ",e->d_name);
			/*char *actualTarget;
			strcpy(actualTarget,tardir);
			strcat(actualTarget,"/");
			strcat(actualTarget,Path);
			int l= strlen(Path);
			int i=l-1;*/
			/*do{
				actualTarget[i] = '\0';
				i--;
			}while(actualTarget[i]!='/');*/
			//printf("sent actualTarget = %s ",actualTarget);
			copy_file( e->d_name, tardir , Path);
                }
            }
        }
    }
	else {
		printf("not a dir fname is = %s\n ", spath);
		copy_file( spath, tardir,NULL);
	}
}




void copy_file( char *filename, char *dirname , char * to_append){



	int sz;
	//printf("%s\n",argv[1]);
	printf("received fname is = %s \n",filename);
	printf("tardir is %s\n",dirname);
	printf("to append is %s\n",to_append);
	
	char actualDir[100];int i;char *actualTarget;
	if(to_append!=NULL){
	for( i=0;i<strlen(dirname);i++){
		actualDir[i]=dirname[i];
	}
	actualDir[i]='/';
	i++;
	for(int j=0;j<strlen(to_append);j++){
		actualDir[i]=to_append[j];i++;
	}
	printf("appended is %s\n",actualDir);
	int j=strlen(actualDir)-1;
	do{
		actualDir[j]='\0';
		j--;
	}while(actualDir[j]!='/');
	actualDir[j]='\0';
	printf("actual path after appended is %s\n",actualDir);
	actualTarget = (char *)actualDir;
	}
	/*read from file */
	//char *buf = (char *) calloc (100, sizeof(char));
	int fd = open(filename, O_RDONLY);
	char buf[17];
	/*sz = read(fd,buf,16);
	while(sz>0){
	//printf("called read(%d ,buf,10 ) returned %d bytes were read\n",fd,sz);
	buf[16]='\0';
	printf("%s ",buf);
	sz = read(fd,buf,16);
	}*/
	int chdirval;
	if(to_append!=NULL)
	 chdirval= chdir(actualTarget);
	else
		chdirval= chdir(dirname);
	printf("chdir returned val is %d\n",chdirval);
	
	

	int fd_for_w = open(filename, O_RDWR | O_CREAT , 0700);
	printf("file descriptor fd_for_w = %d\n",fd_for_w);
	if(fd_for_w == -1){
		//printf ("error number %d\n", errno);
		perror("program");
	}
	printf("file opened \n");
	int sz1;
	sz = read(fd,buf,16);
	while(sz>0){
	//printf("called read(%d ,buf,10 ) returned %d bytes were read\n",fd,sz);
	buf[16]='\0';
	//printf("%s ",buf);
	sz = read(fd,buf,16);
	sz1 = write(fd_for_w, buf,strlen(buf));
	}
	//file close
	/*file close*/
	int close_id = close (fd);
	if(close_id < 0){
		printf("erroe while closeoing\n");
		perror("c1");
		exit(1);
	}
	printf("file clsoed");
	close_id = close (fd_for_w);
	if(close_id < 0){
		printf("erroe while closeoing\n");
		perror("c1");
		exit(1);
	}
	
	printf("file clsoed");
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
     		 perror("getcwd() error");
        else
      		printf("current working directory is: %s\n", cwd);




}
