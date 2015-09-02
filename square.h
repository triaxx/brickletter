#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "color.h"

typedef enum
{
  STANDARD,
  HIGHLIGHTED,
  CURSOR,
  EMPTY,
} square_type_t;

typedef struct
{
  color_t color;
  square_type_t type;
} square_t;

void square_print(const square_t square);
int square_is_highlighted(const square_t square);

#endif /* __SQUARE_H__ */
