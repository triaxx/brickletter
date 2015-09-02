#include <stdio.h>
#include <stdlib.h>

#include "color.h"

#define BOLD     1
#define REVERSED 7

static char color_get_char(const color_t color)
{
  switch (color)
  {
    case RED:    return 'R';
    case GREEN:  return 'G';
    case BLUE:   return 'B';
    case YELLOW: return 'Y';
    case ORANGE: return 'O';
    default:     return '#';
  }
}

void color_print_standard_char(const color_t color)
{
  printf("%c", color_get_char(color));
}

static void color_print_colored_char(const color_t color, unsigned int type)
{
  unsigned char id = 0;

  switch (color)
  {
    case RED:    id = 1;
                 break;
    case GREEN:  id = 28;
                 break;
    case BLUE:   id = 18;
                 break;
    case YELLOW: id = 3;
                 break;
    case ORANGE: id = 130; 
                 break;
    default:     id = 232;
  }
  printf("\e[%u;38;5;%dm%c\e[0m", type, id, color_get_char(color));
}

void color_print_highlighted_char(const color_t color)
{
  color_print_colored_char(color, BOLD);
}

void color_print_cursor_char(const color_t color)
{
  color_print_colored_char(color, REVERSED);
}

void color_print_empty_char(const color_t color)
{
  printf(" ");
}

color_t color_rand()
{
  return rand() % NB_COLOR;
}
