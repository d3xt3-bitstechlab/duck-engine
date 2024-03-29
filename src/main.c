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

/***

IF IT'S IN THE MAIN AND IT'S
NOT THE MAIN(); FUNCTION IT'S
BECAUSE I'M STILL DEVELOPING IT!

***/

void	refresh(t_window *w, t_list *l, t_text *t, t_font *f, t_image *img)
{
  t_elem *e;
  char *text_save;
  t_elem_text *e_text;

  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 100);
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
      text_save = strdup(e_text->data);
      text_module(text_save, w, f);
    }
  if (img->image_show == 1)
    {
      img->image = IMG_Load(img->image_name);
      SDL_BlitSurface(img->image, NULL, w->screen, &img->posImage);
    }
  SDL_Flip(w->screen);
}

void	pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int	fd;
  char	*s;
  t_image img;

  if (m->DUCK_isPlaying == 1 && m->DUCK_TitleMusic == 1)
    {
      music_close(m);
      m->DUCK_TitleMusic = 0;
    }
  img.image_show = 0;
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      text_history(t);
      scene_text(s, t);
      scene_show(s, l);
      scene_unshow(s, l);
      scene_background(s, w);
      scene_music(s, m);
      scene_se(s, m);
      scene_image(s, &img);
      if (!strncmp(s, ">end", 4))
	clean_exit(w, m, l, t);
      if (!strncmp(s, ">>w", 3))
	events2(w, m, l, t, f, &img);
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
  printf("%sWELCOME TO %sDUCK-ENGINE%s%s ALPHA 0.1.9%s\n", "\033[04;29m", "\033[01;32m", "\033[00m", "\033[04;29m", "\033[00m");
  printf("initialiazing SDL... ");
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  printf("done\n");
  printf("initialiazing SDL_ttf... ");
  if (TTF_Init() == -1)
    show_error(4);
  printf("done\n");
  printf("initialiazing window... ");
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
