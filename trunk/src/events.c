/*
** events.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Mon Jun 18 10:50:02 2012 
** Last update Mon Jun 18 11:44:18 2012 
*/

#include "header.h"
#include "text.h"

void	events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  SDL_Event event;
  int	continuer;

  continuer = 1;
  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  clean_exit(w, m, l);
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    pars_scene(w, m, l, t, f);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_RETURN:
	      pars_scene(w, m, l, t, f);
	      break;
	    case SDLK_SPACE:
	      pars_scene(w, m, l, t, f);
	      break;
	    case SDLK_ESCAPE:
	      clean_exit(w, m, l);
	      break;
	    default:
	      break;
            }
	  break;
	default:
	  break;
	}
    }
}

void	events(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  SDL_Event event;
  int	continuer;

  continuer = 1;
  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  continuer = 0;
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    pars_scene(w, m, l, t, f);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      continuer = 0;
	      break;
	    case SDLK_RETURN:
	      pars_scene(w, m, l, t, f);
	      break;
	    default:
	      break;
            }
	  break;
	default:
	  break;
	}
    }
}
