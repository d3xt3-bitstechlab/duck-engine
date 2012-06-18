/*
** open_fd.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Mon Jun 18 10:28:02 2012 
** Last update Mon Jun 18 10:29:15 2012 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	open_fd(char *str)
{
  static int fd;

  if (!fd)
    if ((fd = open(str, O_RDONLY)) < 0)
      return (-1);
  return (fd);
}
