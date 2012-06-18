/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include <stdlib.h>
#include <string.h>

char    *limit_char(char *str, int i, int limit)
{
  int   j;
  int   k;
  char  *result;

  j = i;
  k = 0;
  result = malloc(strlen(str) + 1);
  memset(result, 0, strlen(str) + 1);
  while (str[j])
    {
      if (j == limit)
        return (result);
      result[k] = str[j];
      ++j;
      ++k;
    }
  return (result);
}
