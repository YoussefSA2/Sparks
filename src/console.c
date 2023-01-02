/**
 * @file console.c
 * @brief File containing functions to manipulate the user interactions with the console.
 * @author Charles-Meldhine Madi Mnemoi, Youssef Said
*/

#include "./include/console.h"

/**
 * @brief This function allows to wait for the user to enter a string without pressing enter.
*/
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

/**
* @brief Returns the player input.
* @return The player input.
*/
char getPlayerInput() {
    while (!kbhit()) {}
    char input = getchar();
    return input;
    
}