#include <ctype.h>
#include <stdio.h>
#include <unistd.h> //provides access to various POSIX (Portable Operating System Interface) system calls and constants.
#include <termios.h> 
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); //set the terminal attributes of stdin to the original values
}


void enableRawMode(){   
     tcgetattr(STDIN_FILENO, &orig_termios); 
     atexit(disableRawMode);
     struct termios raw = orig_termios;
     raw.c_iflag &= ~(ICRNL | IXON);
     raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
     tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }


int main(){
    enableRawMode(); //enable raw mode for terminal

    char c;
    //reading the keyword inputs, one byte at a time and stores in c variable
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){ //and if the last key is q then "quit"
     if (iscntrl(c)) { //if it is a non printiable charactor then this 
      printf("%d\n", c);
    } else { //otherwise this
      printf("%d ('%c')\n", c, c);
    }
}
      return 0;
}