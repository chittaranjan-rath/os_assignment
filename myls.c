// This program in similar to shell command ls.

//	Compile: 	gcc   myls.c
//	Run: 	a.out   
//    or	Run: 	a.out   anyfilename.c   anydirectoryname1    directoryname2  


#include <stdio.h>
#include <sys/types.h>      // for typedefs 
#include <dirent.h>     // directory entry structure, for struct dirent and DIR

void listfile(char name[]);



int main (int argc, char *argv[])
{
   if (argc == 1)
   {  
     // default: print file names in the current directory
      listfile(".");
   }
   else
      while (--argc > 0)
      {
	     // print out directory name first
         printf("%s\n", *++argv);
		 // then print out all file names in the directory
         listfile(*argv);
      }

   return 0;
}


// print file names for name
void listfile(char name[])
{
   struct dirent *direntpointer;
   DIR *direct;
  
   if ((direct=opendir(name)) == NULL)	 // opendir function sets up a connection between directory on disk and the process buffer
   {
      fprintf(stderr, "myls: can't open %s\n", name);
      return;
   }
   else
   {
	  while ((direntpointer=readdir(direct)) != NULL) // readdir reads a record from the connection
		printf("%s\n", direntpointer->d_name);

      closedir(direct); // close the connection
   }
} // listfile



