/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "list.h"
#include "header.h"
#include "get_next_line.h"

void	pars_list2(t_list *l, char *s)
{
  int	i;
  int	j;
  char	*name;
  char	*img;

  if (!strncmp(s, ">>", 2))
    {
      name = xmalloc(512);
      memset(name, 0, 512);
      img = xmalloc(512);
      memset(img, 0, 512);
      for (j = 0, i = 2 ; s[i] ;)
	{
	  if (s[i] == ' ' && s[i + 1] == '=')
	    break;
	  name[j++] = s[i++];
	}
      for (i += 4, j = 0 ; s[i] ;)
	{
	  if (s[i] == '"')
	    break;
	  img[j++] = s[i++];
	}
      ins_end_list(l, name, img);
      free(name);
      free(img);
    }
}

void	pars_list(t_list *l)
{
  int	fd;
  char	*s;

  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      if (!strncmp(s, ">scene", 6))
	break;
      pars_list2(l, s);
   }
}
