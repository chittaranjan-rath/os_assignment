#include<stdio.h> //perror()
#include<stdlib.h> //atexit() exit()
#include <unistd.h> //write() STDOUT_FILENO
#include <termios.h> //ISIG ICANON VMIN VTIME
#include <ctype.h> //iscntrl()
#include <errno.h>

void enableRawMode() ;
void disableRawMode();
void die(const char *s);
char editorReadKey(); //wait for 1 keypress and return it
void editorProcessKeypress() ; //wait for a keypress and handle it
void editorRefreshScreen(); //clear screen
