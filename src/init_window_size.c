/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"

SDL_Surface	*init_window_size(SDL_Surface *screen, char *s, t_window *w)
{
  int	i;
  int	j;

  w->sizeY = xmalloc(6);
  w->sizeX = xmalloc(6);
  memset(w->sizeX, 0, 6);
  memset(w->sizeY, 0, 6);
  if (s[15] != '"')
    {
      for (j = 0, i = 15 ; s[i] != ',';)
	w->sizeX[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != '"';)
	w->sizeY[j++] = s[i++];
      if ((screen = SDL_SetVideoMode(atoi(w->sizeX), atoi(w->sizeY),
				     32, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
    }
  else
    {
      if ((screen = SDL_SetVideoMode(1000, 750, 32,
				     SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
      w->sizeX = strdup("1000");
      w->sizeY = strdup("750");
    }
  return (screen);
}
