/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/***

LOL I OPEN A FD

***/

int	open_fd(char *str)
{
  static int fd;

  if (!fd)
    if ((fd = open(str, O_RDONLY)) < 0)
      return (-1);
  return (fd);
}
