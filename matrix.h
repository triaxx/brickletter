#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "square.h"

typedef struct
{
  square_t **squares;
  size_t width;
  size_t height;
} matrix_t;

matrix_t *matrix_new(const size_t width, const size_t height);
void matrix_free(matrix_t *matrix);
size_t matrix_get_width(const matrix_t * const matrix);
size_t matrix_get_height(const matrix_t * const matrix);
void matrix_clear_highlights(const matrix_t *matrix);
void matrix_update(const matrix_t *matrix);
void matrix_highlight_squares(const matrix_t *matrix,
    const unsigned int x, const unsigned int y,
    square_type_t type);
void matrix_print_square(const matrix_t * const matrix,
    const unsigned int x, const unsigned int y);

#endif /* __MATRIX_H__ */
