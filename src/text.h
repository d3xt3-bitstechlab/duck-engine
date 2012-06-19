/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#ifndef __DUCK_ENGINE_TEXT__
#define __DUCK_ENGINE_TEXT__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "xmalloc.h"

typedef struct s_elem_text
{
  char	*data;
  struct s_elem_text *next;
  struct s_elem_text *prev;
} t_elem_text;

typedef struct s_text
{
  int	size;
  t_elem_text        *head;
  t_elem_text        *tail;
} t_text;

void    init_list_text(t_text *l);
void    del_elem_text(t_elem_text *e, t_text *l);
void    show_list_text(t_text *l);
int     ins_end_list_text(t_text *l, char *data);

#endif
