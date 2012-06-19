/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/  
*/

#include "header.h"

void    text_history(t_text *t)
{
  t_elem_text *e;

  if (t->size == 11)
    {
      e = t->head;
      del_elem_text(e, t);
    }
}
