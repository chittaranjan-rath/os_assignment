#include<stdio.h> //perror()
#include<stdlib.h> //atexit() exit()
#include <unistd.h>
#include <termios.h> //ISIG ICANON VMIN VTIME
#include <ctype.h> //iscntrl()
#include <errno.h>

void enableRawMode() ;
void disableRawMode();
void die(const char *s);
