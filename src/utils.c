#include "./include/utils.h"

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
 * @brief Returns a random integer between min and max.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer between min and max.
*/
unsigned int randomInteger(unsigned int min, unsigned int max)
{
    srand(time(NULL) + rand());
    unsigned int value = rand() % (max - min + 1) + min;
    return value;
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