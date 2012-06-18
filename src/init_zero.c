/*
** init_zero.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Mon Jun 18 10:34:18 2012 
** Last update Mon Jun 18 10:36:52 2012 
*/

#include "list.h"

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
