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
