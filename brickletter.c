/* Copyright (c) 2015, Frédéric Fauberteau
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.#include <stdio.h>
 */

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
