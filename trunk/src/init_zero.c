/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "list.h"

/***

to set that all caracters, are,
by default, unshown.

***/

void	init_zeroes(t_list *l)
{
  t_elem *e;

  e = l->head;
  while (e)
    {
      e->is_show = 0;
      e = e->next;
    }
}
