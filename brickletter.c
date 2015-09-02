#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "board.h"

#define TERM_W (80)
#define TERM_H (24)
#define STR_MAX (256)

char *program_name;
struct termios backup_termios;

static void brickletter_init();
static void brickletter_start();
static void restore_termios();

int main(int argc, char **argv)
{
  program_name = argv[0];
  atexit(restore_termios);

  brickletter_start();

  return EXIT_SUCCESS;
}

void brickletter_init()
{
  struct termios termios;

  /* init random seed */
   srand(time(NULL));
  /*srand(0);*/
  /* get the terminal settings for stdin */
  if (tcgetattr(STDIN_FILENO, &backup_termios))
    goto error;
  termios = backup_termios;
  /* disable canonical mode (buffered i/o) and local echo */
  termios.c_lflag &= (~ICANON & ~ECHO);
  /* set the new settings immediately */
  if (tcsetattr(STDIN_FILENO, TCSANOW, &termios))
    goto error;

  return;
error:
  perror(program_name);
  exit(EXIT_FAILURE);
}

void brickletter_start()
{
  board_t *board;
  char key = 0;

  brickletter_init();
  board = board_new(TERM_W, TERM_H);
  do
  {
    board_update(board, key);
    board_print(board);
    scanf("%c", &key);
  } while (key != 'q');
  board_free(board);
}

static void restore_termios()
{
  if (tcsetattr(STDIN_FILENO, TCSANOW, &backup_termios))
    goto error;

  return;
error:
  perror(program_name);
}
