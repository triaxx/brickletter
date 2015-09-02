#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

extern char *program_name;

matrix_t *matrix_new(const size_t width, const size_t height)
{
  matrix_t *matrix;
  unsigned int x;
  unsigned int y;

  matrix = malloc(sizeof(matrix_t));
  if (!matrix)
    goto error;
  matrix->squares = malloc(width * sizeof(square_t *));
  if (!matrix->squares)
    goto error;
  for (x = 0U; x < width; ++x)
  {
    matrix->squares[x] = malloc(height * sizeof(square_t));
    if (!matrix->squares[x])
      goto error;
    for (y = 0U; y < height; ++y)
    {
      matrix->squares[x][y].color = color_rand();
    }
  }
  matrix->width = width;
  matrix->height = height;

  return matrix;
error:
  perror(program_name);
  exit(EXIT_FAILURE);
}

void matrix_free(matrix_t *matrix)
{
  unsigned int x;

  for (x = 0U; x < matrix->width; ++x)
  {
    free(matrix->squares[x]);
  }
  free(matrix->squares);
  free(matrix);
}

size_t matrix_get_width(const matrix_t * const matrix)
{
  return matrix->width;
}

size_t matrix_get_height(const matrix_t * const matrix)
{
  return matrix->height;
}

void matrix_clear_highlights(const matrix_t *matrix)
{
  unsigned int x;
  unsigned int y;

  for (x = 0U; x < matrix->width; ++x)
  {
    for (y = 0U; y < matrix->height; ++y)
    {
      if (square_is_highlighted(matrix->squares[x][y]))
      {
        matrix->squares[x][y].type = STANDARD;
      }
    }
  }
}

static void matrix_update_column(const matrix_t *matrix,
    const unsigned int x, const unsigned int y_start)
{
  unsigned int y = y_start;
  unsigned int cur;
  unsigned int bound = 1U;

  while (y >= bound)
  {
    if (square_is_highlighted(matrix->squares[x][y]))
    {
      for (cur = y; cur >= bound; --cur)
      {
        matrix->squares[x][cur] = matrix->squares[x][cur - 1];
      }
      matrix->squares[x][cur].type = EMPTY;
      bound++;
    }
    else
    {
      y--;
    }
  }
  if (square_is_highlighted(matrix->squares[x][y]))
  {
    matrix->squares[x][y].type = EMPTY;
  }
}

static void matrix_update_line(const matrix_t *matrix, const unsigned int x_start)
{
  unsigned int x;
  unsigned int y;

  for (x = x_start; x > 0; --x)
  {
    for (y = 0U; y < matrix->height; ++y)
    {
      matrix->squares[x][y] = matrix->squares[x-1][y];
    }
  }
  for (y = 0U; y < matrix->height; ++y)
  {
    matrix->squares[0][y].type = EMPTY;
  }
}

void matrix_update(const matrix_t *matrix)
{
  unsigned int x;
  int y;

  /* update verticaly (gravity) */
  for (x = 0U; x < matrix->width; ++x)
  {
    for (y = matrix->height - 1; y >= 0; --y)
    {
      if (square_is_highlighted(matrix->squares[x][y]))
      {
        matrix_update_column(matrix, x, y);
      }
    }
  }
  /* update horizontaly */
  for (x = 1U; x < matrix->width; ++x)
  {
    if (matrix->squares[x][matrix->height - 1].type == EMPTY)
    {
      matrix_update_line(matrix, x);
    }
  }
}

void matrix_highlight_squares(const matrix_t *matrix,
    const unsigned int x, const unsigned int y,
    square_type_t type)
{
  struct
  {
    int x;
    int y;
  } neighbors[4] =
  {
    { x + 1, y },
    { x - 1, y },
    { x, y + 1 },
    { x, y - 1 }
  };
  unsigned int i;

  matrix->squares[x][y].type = type;
  if (type == CURSOR)
    type = HIGHLIGHTED;
  for (i = 0U; i < 4U; ++i)
  {
    if (neighbors[i].x >= 0 && neighbors[i].x < matrix->width &&
        neighbors[i].y >= 0 && neighbors[i].y < matrix->height)
    {
      square_t neighbor = matrix->squares[neighbors[i].x][neighbors[i].y];
      if (neighbor.color == matrix->squares[x][y].color &&
          !square_is_highlighted(neighbor) && !(neighbor.type == EMPTY))
      {
        matrix_highlight_squares(matrix, neighbors[i].x, neighbors[i].y, type);
      }
    }
  }
}

void matrix_print_square(const matrix_t * const matrix,
    const unsigned int x, const unsigned int y)
{
  square_print(matrix->squares[x][y]);
}
