#include<stdio.h> //perror()
#include<stdlib.h> //atexit() exit()
#include <unistd.h> //write() STDOUT_FILENO
#include <termios.h> //ISIG ICANON VMIN VTIME
#include <ctype.h> //iscntrl()
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h> //in op ctrl terminal size
void enableRawMode() ;
void disableRawMode();
void die(const char *s);
char editorReadKey(); //wait for 1 keypress and return it
void editorProcessKeypress() ; //wait for a keypress and handle it
void editorRefreshScreen(); //clear screen
void editorDrawRows(struct abuf *ab);
int getWindowSize(int *rows, int *cols);
void initEditor();
int getCursorPosition(int *rows, int *cols);
void abFree(struct abuf *ab);
void abAppend(struct abuf *ab, const char *s, int len);
void editorMoveCursor(int key);
