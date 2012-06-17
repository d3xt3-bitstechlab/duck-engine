/*
** limit_char.c for  in /home/marcha_r/Dropbox/perso/duck-engine
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Sun Jun 17 17:30:13 2012 
** Last update Sun Jun 17 17:31:46 2012 
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
