/*
** xmalloc.c for  in /home/marcha_r/Dropbox/projects/42sh/home/marcha_r
** 
** Made by theo marchal
** Login   <marcha_r@epitech.net>
** 
** Started on  Thu Apr  5 17:59:17 2012 theo marchal
** Last update Wed Jun  6 14:16:43 2012 
*/

#include <stdio.h>
#include "xmalloc.h"

void    *xmalloc(unsigned int u)
{
  void  *p;

  p = malloc(u);
  if (p == 0)
    {
      printf("duck-engine: bad allocation.\n");
      exit(0);
    }
  return (p);
}
