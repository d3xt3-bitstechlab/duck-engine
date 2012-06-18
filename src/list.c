/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "list.h"

void    show_error(int error);

void	init_list(t_list *l)
{
  l->tail = 0;
  l->head = 0;
  l->size = 0;
}

void	del_elem(t_elem *e, t_list *l)
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

void	show_list(t_list *l)
{
  t_elem	*e;

  e = l->head;
  while (e)
    {
      printf("%s ||| %s\n", e->name, e->img);
      e = e->next;
    }
}

int	ins_end_list(t_list *l, char *name, char *img)
{
  t_elem	*e;

  e = xmalloc(sizeof(*e));
  e->name = strdup(name);
  e->img = strdup(img);
  if ((e->perso = IMG_Load(img)) == NULL)
    show_error(5);
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
