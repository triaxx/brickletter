#ifndef __COLOR_H__
#define __COLOR_H__

typedef enum
{
  RED,
  GREEN,
  BLUE,
  YELLOW,
  ORANGE,
  NB_COLOR,
} color_t;

void color_print_standard_char(const color_t color);
void color_print_highlighted_char(const color_t color);
void color_print_cursor_char(const color_t color);
void color_print_empty_char(const color_t color);
color_t color_rand();

#endif /* __COLOR_H__ */
