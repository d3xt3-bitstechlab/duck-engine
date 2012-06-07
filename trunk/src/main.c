/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Thu Jun  7 18:12:42 2012 
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "get_next_line.h"
#include "xmalloc.h"
#include "list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define KEYSTATES Uint8 *keystates = SDL_GetKeyState(NULL)

typedef struct s_window
{
  SDL_Surface *screen;
  SDL_Surface *background;
  SDL_Rect posBack;
} t_window;

void	show_error(int error)
{
  printf("%s!!!FATAL ERROR!!!%s\nduck-engine: ", "\033[01;31m", "\033[00m");
  if (error == 0)
    printf("SDL error: %s\n", SDL_GetError());
  if (error == 1)
    printf("no background title image set.\n");  
  if (error == 2)
    printf("no script.duck file found.\n");
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

void	events()
{
  int	quit;
  SDL_Event event;
  KEYSTATES;

  quit = 0;
  while (quit == 0)
    {
      while (SDL_PollEvent(&event))
        {
          if (event.type == SDL_QUIT)
            quit = 1;
          if (keystates[SDLK_ESCAPE])
	    quit = 1;
        }
    }
}

void	pars_list(t_list *l)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*name;
  char	*img;

  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      if (!strncmp(s, ">scene", 6))
	break;
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
	  i += 4;
	  for (j = 0 ; s[i] ;)
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
  show_list(l);
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
				     32, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
    }
  else
    if ((screen = SDL_SetVideoMode(1000, 750, 32,
				   SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
      show_error(0);
  free(sizeX);
  free(sizeY);
  return (screen);
}

void	init_window(t_window *w)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*title;
  char	*icon;
  char	*back;

  w->posBack.x = 0;
  w->posBack.y = 0;
  title = xmalloc(512);
  memset(title, 0, 512);
  icon = xmalloc(512);
  memset(icon, 0, 512);
  back = xmalloc(512);
  memset(back, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      if (!strncmp(s, ">caracters", 10))
	break;
      if (!strncmp(s, "WINDOW_SIZE = \"", 15))
	w->screen = init_window_size(w->screen, s);
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
      if (!strncmp(s, "BACKGROUND_TITLE = \"", 20))
	{
	  if (s[20] != '"')
	    for (j = 0, i = 20 ; s[i] != '"';)
	      back[j++] = s[i++];
	  else
	    show_error(1);
	  w->background = IMG_Load(back);
	  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
	  SDL_Flip(w->screen);
	}
    }
  SDL_WM_SetCaption(title, icon);
  free(title);
  free(icon);
  free(back);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  t_list l;
  t_window w;

  w.screen = NULL;
  w.background = NULL;
  if (SDL_Init(/*SDL_INIT_AUDIO |*/ SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  init_window(&w);
  init_list(&l);
  pars_list(&l);
  events();
  SDL_FreeSurface(w.screen);
  SDL_FreeSurface(w.background);
  SDL_Quit();
  return (0);
}
