/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
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
