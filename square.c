#include <stdio.h>
#include <stdlib.h>

#include "square.h"

extern char *program_name;

void square_print(const square_t square)
{
  switch (square.type)
  {
    case STANDARD:    color_print_standard_char(square.color);
                      break;
    case HIGHLIGHTED: color_print_highlighted_char(square.color);
                      break;
    case CURSOR:      color_print_cursor_char(square.color);
                      break;
    case EMPTY:       color_print_empty_char(square.color);
                      break;
    default: goto error;
  }
  
  return;
error:
  fprintf(stderr, "%s: Invalid square type\n", program_name);
  exit(EXIT_FAILURE);
}

int square_is_highlighted(const square_t square)
{
  return square.type == HIGHLIGHTED || square.type == CURSOR;
}
