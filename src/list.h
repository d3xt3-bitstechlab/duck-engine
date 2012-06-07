/*
** list.h for  in /home/marcha_r/Dropbox/42sh-2016-marcha_r/home/marcha_r
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Tue May  1 16:37:22 2012 
** Last update Wed Jun  6 17:45:54 2012 
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xmalloc.h"

typedef struct s_elem
{
  char          *data;
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
int     ins_end_list(t_list *l, char *data);