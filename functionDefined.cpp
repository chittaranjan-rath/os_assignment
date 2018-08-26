#include "functionDeclared.h"
struct termios originalTermiosValue;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH , &originalTermiosValue);
	die("tcsetattr");
}

void enableRawMode() {
 
	tcgetattr(STDIN_FILENO, &originalTermiosValue);
	atexit(disableRawMode);
	struct termios raw = originalTermiosValue;
	raw.c_iflag &= ~(IXON); //ctrl s disabled
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //c_lflag is local flags anding with echo sets 4th bit in flag field off
	//ICANON turns off cannonical mode
	// ISIG diables ctrl c ctrl z
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  // struct termios, tcgetattr(), tcsetattr(), ECHO, and TCSAFLUSH are from termios.h
  // TCSAFLUSH asks tcsetattr to wait till all pending output	is written to terminal then apply changes
}



