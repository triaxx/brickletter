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

#include "cursor.h"

extern char *program_name;

cursor_t *cursor_new(const unsigned int x, const unsigned int y)
{
  cursor_t *cursor = NULL;

  cursor = malloc(sizeof(cursor_t));
  if (!cursor)
    goto error;
  cursor->x = x;
  cursor->y = y;

  return cursor;
error:
  perror(program_name);
  exit(EXIT_FAILURE);
}

void cursor_free(cursor_t *cursor)
{
  free(cursor);
}

static int cursor_is_valid(const int x, const int y, const matrix_t * matrix)
{
  if (x >= 0 && x < matrix->width &&
      y >= 0 && y < matrix->height &&
      matrix->squares[x][y].type != EMPTY)
  {
    return 1;
  }
  return 0;
}

void cursor_update(cursor_t * const cursor, const char key,
    const matrix_t * const matrix)
{
  int new_x = cursor->x;
  int new_y = cursor->y;

  switch (key)
  {
    case 'h': new_x -= 1; break;
    case 'l': new_x += 1; break;
    case 'k': new_y -= 1; break;
    case 'j': new_y += 1; break;
    default:  break;
  }
  if (cursor_is_valid(new_x, new_y, matrix))
  {
    cursor->x = new_x;
    cursor->y = new_y;
  }
}

int cursor_replace(cursor_t * const cursor, const matrix_t * const matrix)
{
  int x = cursor->x;
  int y = cursor->y;

  /* go down cursor */
  if (matrix->squares[x][y].type == EMPTY)
  {
    while (y < matrix->height - 1 && matrix->squares[x][y].type == EMPTY)
    {
      y += 1;
    }
  }
  else
    goto end;
  if (matrix->squares[x][y].type == EMPTY)
  {
    /* cursor is at bottom */
    do
    {
      x += 1;
    }
    while (x < matrix->width - 1 && matrix->squares[x][y].type == EMPTY);
  }
  else
    goto end;
  if (matrix->squares[x][y].type == EMPTY)
  {
    /* cursor is at bottom right */
    do
    {
      x -= 1;
    } while (x > 0 && matrix->squares[x][y].type == EMPTY);
  }
  else
    goto end;
  /* cursor is at bottom left */
  if (matrix->squares[x][y].type == EMPTY)
  {
    /* the game ends */
    return 1;
  }
end:
  cursor->x = x;
  cursor->y = y;
  return 0;
}

unsigned int cursor_get_x(const cursor_t * const cursor)
{
  return cursor->x;
}

unsigned int cursor_get_y(const cursor_t * const cursor)
{
  return cursor->y;
}
