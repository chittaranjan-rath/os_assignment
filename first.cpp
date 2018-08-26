#include "functionDeclared.h"
#define CTRL_KEY(k) ((k) & 0x1f)

int main(){
	enableRawMode();
	/*while (1) {
		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		 if (c == CTRL_KEY('q')) break;
  	}*/
	
	while (1) {
		editorRefreshScreen();
    		editorProcessKeypress();
	}
	return 0;
	
}
