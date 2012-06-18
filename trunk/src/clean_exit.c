/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "list.h"
#include "header.h"

void	clean_exit(t_window *w, t_music *m, t_list *l)
{
  t_elem	*e;

  printf(" done\ncleaning...");
  e = l->head;
  while (e)
    {
      free(e->name);
      free(e->img);
      SDL_FreeSurface(e->perso);
      e = e->next;
    }
  SDL_FreeSurface(w->screen);
  SDL_FreeSurface(w->background);
  if (m->DUCK_isPlaying == 1)
    music_close(m);
  free(w->sizeX);
  free(w->sizeY);
  printf(" done\n");
  printf("exiting...");
  TTF_Quit();
  SDL_Quit();
  printf(" done\n");
  exit(0);
}
