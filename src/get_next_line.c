/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

static void*	deadline(char* new, char* buff)
{
  if (*new)
    free(new);
  free(buff);
  return (NULL);
}

int	readlen(int nbread, short setmod)
{
  static int	sav;
  if (setmod)
    sav = nbread;
  return (sav);
}

static short	mallocline(int i, const int fd, char** buff)
{
  static int	nbread;

  if (i == __READ__)
    {
      *buff = malloc((__READ__) * sizeof(char) + 1);
      nbread = read(fd, *buff, __SIZE_BUFF_OUT__);
      readlen(nbread, 1);
      (*buff)[nbread] = 0;
      if (nbread == 0)
	return (0);
      return (1);
    }
  else
    return (0);
}

char*	get_next_line(const int fd)
{
  static unsigned int	i = __READ__;
  static char*		buff;
  static char*		new;
  int			j;

  if (!buff)
    new = malloc(__SIZE_BUFF_OUT__);
  if ((mallocline(i, fd, &buff)) != 0)
    i = 0;
  if (buff == NULL || fd < 0 || readlen(0, 0) < 0 || __READ__ <= 0 || __SIZE_BUFF_OUT__ <= 0)
    return (buff = deadline(new, buff));
  j = 0;
  while ((j <= __SIZE_BUFF_OUT__ ) && (buff[i] != '\n') && (buff[i] != 0))
    {
      new[j] = buff[i];
      ++i;
      ++j;
    }
  new[j] = 0;
  while (buff[i] == '\n')
    ++i;
  if (strlen(new) == 0)
    return (buff = deadline(new, buff));
  return (new);
}
