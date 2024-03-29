/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"

void    text_module_history(char *text, t_window *w, t_font *f);

/***

the first case when using history navigation,
it should be treated apart to avoid
conflicts with the naturel behaviour
of the history navigation.

***/

void	first_left_show(t_window *w, t_text *t, t_font *f, t_list *l)
{
  t_elem *e;
  char	*text_save;
  t_elem_text *e_text;

  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 180);
  e = l->head;
  while (e)
    {
      if (e->is_show == 1)
        SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
      e = e->next;
    }
  SDL_BlitSurface(f->text_support, NULL, w->screen, &w->posBack);
  if (t->size >= 1)
    {
      text_save = xmalloc(4096);
      memset(text_save, 0, 4096);
      e_text = t->tail;
      e_text = e_text->prev;
      text_module_history(e_text->data, w, f);
    }
  SDL_Flip(w->screen);
}

/***

history_show(); is the function called
to blit the text while using the
text navigation.

***/

void	history_show(t_window *w, t_text *t, t_font *f, t_elem_text *e_text, t_list *l)
{
  t_elem *e;
  char	*text_save;

  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 180);
  e = l->head;
  while (e)
    {
      if (e->is_show == 1)
        SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
      e = e->next;
    }
  SDL_BlitSurface(f->text_support, NULL, w->screen, &w->posBack);
  if (t->size >= 1)
    {
      text_save = xmalloc(4096);
      memset(text_save, 0, 4096);
      text_module_history(e_text->data, w, f);
    }
  SDL_Flip(w->screen);
}

/***

loop for the navigation between text with arrows.
conditions = important, if not, segfault!!

***/

void	history_navigation(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img)
{
  int   next;
  SDL_Event event;
  t_elem_text *e_text;

  next = 1;
  e_text = t->tail;
  if (e_text->prev != NULL)
    e_text = e_text->prev;
  first_left_show(w, t, f, l);
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
	      events2(w, m, l, t, f, img);
              break;
            case SDLK_SPACE:
	      next = 0;
	      events2(w, m, l, t, f, img);
              break;
            case SDLK_LEFT:
	      if (e_text->prev != NULL)
		{
		  e_text = e_text->prev;
		  history_show(w, t, f, e_text, l);
		}
              break;
            case SDLK_RIGHT:
	      if (e_text->next != NULL && e_text->next->next != NULL)
		{
		  e_text = e_text->next;
		  history_show(w, t, f, e_text, l);
		}
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
