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
