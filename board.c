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

#include "board.h"
#include "cursor.h"
#include "matrix.h"

extern char *program_name;

board_t *board_new(const size_t width, const size_t height)
{
  board_t *board;

  board = malloc(sizeof(board_t));
  if (!board)
    goto error;
  board->matrix = matrix_new(width - 2, height - 4);
  board->cursor = cursor_new(0, 0);
  board->width = width;
  board->height = height;
  board->nb_group = 0;
  board->score = 0;

  return board;
error:
  perror(program_name);
  exit(EXIT_FAILURE);
}

void board_free(board_t *board)
{
  matrix_free(board->matrix);
  cursor_free(board->cursor);
  free(board);
}

static int board_compute_points(const board_t * const board)
{
  unsigned int n = 0;
  unsigned int x;
  unsigned int y;

  for (x = 0; x < board->matrix->width; ++x)
  {
    for (y = 0; y < board->matrix->height; ++y)
    {
      if (square_is_highlighted(board->matrix->squares[x][y]))
      {
        n++;
      }
    }
  }

  return n * (n - 1);
}

void board_update(board_t * const board, const char key)
{
  cursor_update(board->cursor, key, board->matrix);
  if (key == ' ')
  {
    board->nb_group++;
    board->score += board_compute_points(board);
    matrix_update(board->matrix);
    if (!cursor_replace(board->cursor, board->matrix))
    {
      /* game finishes */
    }
  }
  /* matrix_update() delete highlighted squares then it
   * becomes useless to clear them. */
  else
  {
    matrix_clear_highlights(board->matrix);
  }
  matrix_highlight_squares(board->matrix,
      cursor_get_x(board->cursor), cursor_get_y(board->cursor),
      CURSOR);
}

void board_print(const board_t * const board)
{
  unsigned int x, y;

  /* set cursor at (0,0) */
  printf("\033[0;0H");
  printf("\033[2J");

  for (x = 0U; x < board->width; ++x)
  {
    printf("-");
  }
  printf("\n");
  for (y = 0U; y < matrix_get_height(board->matrix); ++y)
  {
    printf("|");
    for (x = 0U; x < matrix_get_width(board->matrix); ++x)
    {
      matrix_print_square(board->matrix, x, y);
    }
    printf("|\n");
  }
  for (x = 0U; x < board->width; ++x)
  {
    printf("-");
  }
  printf("\n");
  /* TODO: Make follow adapted to the board size */
  printf("Group: %3d                                                          Score: %5d\n",
      board->nb_group, board->score);
}
