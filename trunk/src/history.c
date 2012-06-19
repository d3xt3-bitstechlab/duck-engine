/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"

void	first_left_show(t_window *w, t_text *t, t_font *f)
{
  char	*text_save;
  t_elem_text *e_text;

  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 100);
  SDL_BlitSurface(f->text_support, NULL, w->screen, &w->posBack);
  if (t->size >= 1)
    {
      text_save = xmalloc(4096);
      memset(text_save, 0, 4096);
      e_text = t->tail;
      e_text = e_text->prev;
      text_module(e_text->data, w, f);
    }
  SDL_Flip(w->screen);
}

void	history_navigation(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image_scene *img_scn)
{
  int   next;
  SDL_Event event;

  next = 1;
  first_left_show(w, t, f);
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
	      next = 0;
	      events2(w, m, l, t, f, img_scn);
              break;
            case SDLK_SPACE:
              pars_scene(w, m, l, t, f);
              break;
            case SDLK_LEFT:
	      printf("history left\n");
              break;
            case SDLK_RIGHT:
	      printf("history right\n");
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
