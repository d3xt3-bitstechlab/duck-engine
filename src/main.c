/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "xmalloc.h"
#include "list.h"
#include "text.h"
#include "header.h"

void	refresh(t_window *w, t_list *l, t_text *t, t_font *f, t_image_scene *img_scn)
{
  t_elem *e;
  char *text_save;
  t_elem_text *e_text;

  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 100);
  SDL_BlitSurface(f->text_support, NULL, w->screen, &w->posBack);
  e = l->head;
  while (e)
    {
      if (e->is_show == 1)
	SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
      e = e->next;
    }
  if (t->size >= 1)
    {
      text_save = xmalloc(4096);
      memset(text_save, 0, 4096);
      e_text = t->tail;
      text_save = strdup(e_text->data);
      text_module(text_save, w, f);
    }
  if (img_scn->image_show == 1)
    {
      img_scn->image = IMG_Load(img_scn->image_name);
      SDL_BlitSurface(img_scn->image, NULL, w->screen, &img_scn->posImage);
    }
  SDL_Flip(w->screen);
}

void	history_navigation(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int   next;
  SDL_Event event;

  next = 1;
  printf("history left :)\n");
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

void	pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int	fd;
  char	*s;
  t_image_scene img_scn;

  if (m->DUCK_isPlaying == 1 && m->DUCK_TitleMusic == 1)
    {
      music_close(m);
      m->DUCK_TitleMusic = 0;
    }
  img_scn.image_show = 0;
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      ++DUCK_line;
      text_history(t);
      scene_text(s, t);
      scene_show(s, l);
      scene_unshow(s, l);
      scene_background(s, w);
      scene_music(s, m);
      scene_se(s, m);
      scene_image(s, &img_scn);
      if (!strncmp(s, ">end", 4))
	clean_exit(w, m, l, t);
      if (!strncmp(s, ">>w", 3))
	events2(w, m, l, t, f);
      refresh(w, l, t, f, &img_scn);
    }
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  t_list l;
  t_text t;
  t_font f;
  t_music m;
  t_window w;

  w.screen = NULL;
  w.background = NULL;
  m.DUCK_isPlaying = 0;
  m.DUCK_TitleMusic = 0;
  DUCK_line = 2;
  printf("%sWELCOME TO %sDUCK-ENGINE%s%s ALPHA 0.1.7%s\n", "\033[04;29m", "\033[01;32m", "\033[00m", "\033[04;29m", "\033[00m");
  printf("initialiazing SDL... ");
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  printf("done\n");
  printf("initialiazing SDL_ttf... ");
  if (TTF_Init() == -1)
    show_error(4);
  printf("done\n");
  printf("initialiazing window parameters... ");
  init_window(&w, &m, &f);
  printf("done\n");
  init_list(&l);
  printf("parsing caracter list... ");
  pars_list(&l);
  init_zeroes(&l);
  printf("done\n");
  printf("initializing font... ");
  if ((f.font = TTF_OpenFont(f.font_used, f.size_font)) == NULL)
    show_error(4);
  f.text_support = SDL_CreateRGBSurface(SDL_HWSURFACE, atoi(w.sizeX), atoi(w.sizeY),
				      32, 0, 0, 0, 0);
  printf("done\n");
  init_list_text(&t);
  if ((write(1, "showing window...", 17)) == -1)
    show_error(6);
  events(&w, &m, &l, &t, &f);
  clean_exit(&w, &m, &l, &t);
  return (0);
}
