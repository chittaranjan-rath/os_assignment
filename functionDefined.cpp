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
 
	if (tcgetattr(STDIN_FILENO, &originalTermiosValue) == -1) die("tcgetattr");
	atexit(disableRawMode);
	struct termios raw = originalTermiosValue;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	 //ctrl s disabled
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //c_lflag is local flags anding with echo sets 4th bit in flag field off
	//ICANON turns off cannonical mode
	// ISIG diables ctrl c ctrl z
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  // struct termios, tcgetattr(), tcsetattr(), ECHO, and TCSAFLUSH are from termios.h
  // TCSAFLUSH asks tcsetattr to wait till all pending output	is written to terminal then apply changes
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}



