/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "text.h"

void	init_list_text(t_text *l)
{
  l->tail = 0;
  l->head = 0;
  l->size = 0;
}

void	del_elem_text(t_elem_text *e, t_text *l)
{
  if (l->size == 1)
    {
      l->head = NULL;
      l->tail = NULL;
    }
  else if (l->size > 1)
    {
      if (l->head == e)
	{
	  e->next->prev = NULL;
	  l->head = e->next;
	}
      else if (l->tail == e)
	{
	  e->prev->next = NULL;
	  l->tail = e->prev;
	}
      else
	{
	  e->prev->next = e->next;
	  e->next->prev = e->prev;
	  e = e->next;
	}
    }
  l->size--;
}

void	show_list_text(t_text *l)
{
  t_elem_text	*e;

  e = l->head;
  while (e)
    {
      printf("%s\n", e->data);
      e = e->next;
    }
}

int	ins_end_list_text(t_text *l, char *data)
{
  t_elem_text	*e;

  e = xmalloc(sizeof(*e));
  e->data = strdup(data);
  e->next = 0;
  e->prev = l->tail;
  if (!l->tail)
    {
      l->tail = e;
      l->head = e;
    }
  else
    {
      l->tail->next = e;
      l->tail = e;
    }
  l->size++;
  return (0);
}
