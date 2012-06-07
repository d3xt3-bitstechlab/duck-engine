/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Wed Jun  6 23:12:27 2012 
*/

#include "SDL/SDL.h"
#include "get_next_line.h"
#include "xmalloc.h"
#include "list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void	show_error(int error)
{
  printf("!!!ERROR ");
  if (error == 0)
    printf("duck-engine: SDL error: %s\n", SDL_GetError());
  if (error == 1)
    printf("duck-engine: SDL error: %s\n", SDL_GetError());
  if (error == 2)
    printf("duck-engine: no script.duck file found.\n");
  exit(0);
}

int	open_fd(char *str)
{
  static int fd;

  if (!fd)
    if ((fd = open(str, O_RDONLY)) < 0)
      return (-1);
  return (fd);
}

SDL_Surface	*init_window_size(SDL_Surface *screen, char *s)
{
  int	i;
  int	j;
  char	*sizeX;
  char	*sizeY;

  sizeY = xmalloc(6);
  sizeX =  xmalloc(6);
  memset(sizeX, 0, 6);
  memset(sizeY, 0, 6);
  if (s[16] != '"')
    {
      for (j = 0, i = 15 ; s[i] != ',';)
	sizeX[j++] = s[i++];
      for (j = 0, i +=2 ; s[i] != '"';)
	sizeY[j++] = s[i++];
      if ((screen = SDL_SetVideoMode(atoi(sizeX), atoi(sizeY),
				     8, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(1);
    }
  else
    if ((screen = SDL_SetVideoMode(1000, 750, 8,
				   SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
      show_error(1);
  free(sizeX);
  free(sizeY);
  return (screen);
}

void	init_window()
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*title;
  char	*icon;
  SDL_Surface *screen = NULL;

  title = xmalloc(512);
  memset(title, 0, 512);
  icon = xmalloc(512);
  memset(icon, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      if (!strncmp(s, "WINDOW_SIZE = \"", 15))
	screen = init_window_size(screen, s);
      if (!strncmp(s, "WINDOW_TITLE = \"", 16))
	{
	  if (s[16] != '"')
	    for (j = 0, i = 16 ; s[i] != '"';)
	      title[j++] = s[i++];
	  else
	    title = strdup("Duck-Engine : visual novel creator");
	}
      if (!strncmp(s, "WINDOW_ICON = \"", 15))
	{
	  if (s[15] != '"')
	    for (j = 0, i = 15 ; s[i] != '"';)
	      icon[j++] = s[i++];
	  else
	    icon = strdup(".duck-graph/icon.png");
	}
    }
  SDL_WM_SetCaption(title, icon);
  printf("%s, %s\n", title, icon);
  free(title);
  free(icon);
}

void	pars_list(t_list *l)
{
  show_list(l);
}

void	events()
{
  int next = 1;
  SDL_Event event;
 
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
        {
	case SDL_QUIT:
	  next = 0;
        }
    }
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  t_list l;

  if (SDL_Init(/*SDL_INIT_AUDIO |*/ SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  init_window();
  init_list(&l);
  pars_list(&l);
  events();
  SDL_Quit();
  return (0);
}
