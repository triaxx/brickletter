#ifndef __CURSOR_H__
#define __CURSOR_H__

#include "matrix.h"

typedef struct
{
  unsigned int x;
  unsigned int y;
} cursor_t;

cursor_t *cursor_new(const unsigned int x, const unsigned int y);
void cursor_free(cursor_t *cursor);
void cursor_update(cursor_t * const cursor, const char key,
    const matrix_t * const matrix);
int cursor_replace(cursor_t * const cursor, const matrix_t * const matrix);
unsigned int cursor_get_x(const cursor_t * const cursor);
unsigned int cursor_get_y(const cursor_t * const cursor);

#endif /* __CURSOR_H__ */
