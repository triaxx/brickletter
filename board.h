#ifndef __BOARD_H__
#define __BOARD_H__

#include "cursor.h"
#include "matrix.h"

typedef struct
{
  matrix_t *matrix;
  cursor_t *cursor;
  size_t width;
  size_t height;
  unsigned int nb_group;
  unsigned int score;
} board_t;

board_t *board_new(const size_t width, const size_t height);
void board_free(board_t *board);
void board_update(board_t * const board, const char key);
void board_print(const board_t * const board);

#endif /* __BOARD_H__ */
