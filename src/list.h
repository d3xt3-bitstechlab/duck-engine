/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#ifndef __DUCK_ENGINE_LIST__
#define __DUCK_ENGINE_LIST__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "xmalloc.h"

typedef struct s_elem
{
  char          *name;
  char		*img;
  SDL_Surface	*perso;
  SDL_Rect	pos;
  int		is_show;
  struct s_elem *next;
  struct s_elem *prev;
} t_elem;

typedef struct s_list
{
  int           size;
  t_elem        *head;
  t_elem        *tail;
} t_list;

void    init_list(t_list *l);
void    del_elem(t_elem *e, t_list *l);
void    show_list(t_list *l);
int     ins_end_list(t_list *l, char *name, char *img);

#endif
