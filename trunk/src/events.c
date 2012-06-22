/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"
#include "text.h"

void	events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img)
{
  int	next;
  SDL_Event event;

  next = 1;
  refresh(w, l, t, f, img);
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  clean_exit(w, m, l, t);
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
	    case SDLK_LEFT:
	      history_navigation(w, m, l, t, f, img);
	      break;
	    case SDLK_m:
	      music_pause(m);
	      break;
	    case SDLK_ESCAPE:
	      clean_exit(w, m, l, t);
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
  int	next;
  SDL_Event event;

  next = 1;
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  next = 0;
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    pars_scene(w, m, l, t, f);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      next = 0;
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
