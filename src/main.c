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

void	scene_text(char *s, t_text *t)
{
  int	i, j;
  char	*text;

  text = xmalloc(4096);
  memset(text, 0, 4096);
  if (!strncmp(s, "<", 1))
    {
      for (j = 0, i = 1 ; s[i] != '/' && s[i + 1] != '>';)
	text[j++] = s[i++];
      ins_end_list_text(t, text);
    }
  free(text);
}

void	scene_show(char *s, t_list *l)
{
  int	i, j;
  char	*show;
  t_elem *e;
  char	*posPersoX;
  char	*posPersoY;

  show = xmalloc(512);
  memset(show, 0, 512);
  posPersoX = xmalloc(512);
  memset(posPersoX, 0, 512);
  posPersoY = xmalloc(512);
  memset(posPersoY, 0, 512);
  if (!strncmp(s, "show ", 5))
    {
      e = l->head;
      for (j = 0, i = 5 ; s[i] != ' ' ;)
	show[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != ',' ;)
	posPersoX[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != '"' ;)
	posPersoY[j++] = s[i++];
      while (e)
	{
	  if (!strcmp(show, e->name))
	    {
	      e->pos.x = atoi(posPersoX);
	      e->pos.y = atoi(posPersoY);
	      e->is_show = 1;
	    }
	  e = e->next;
	}
    }
  free(show);
  free(posPersoX);
  free(posPersoY);
}

void	scene_unshow(char *s, t_list *l)
{
  int	i, j;
  char	*unshow;
  t_elem *e;

  unshow = xmalloc(512);
  memset(unshow, 0, 512);
  if (!strncmp(s, "unshow ", 7))
    {
      e = l->head;
      for (j = 0, i = 7 ; s[i] ;)
	unshow[j++] = s[i++];
      while (e)
	{
	  if (!strcmp(unshow, e->name))
	    e->is_show = 0;
	  e = e->next;
	}
    }
  free(unshow);
}

void	scene_background(char *s, t_window *w)
{
  int	i, j;
  char	*back;

  back = xmalloc(512);
  memset(back, 0, 512);
  if (!strncmp(s, "background = \"", 14))
    {
      if (s[20] != '"')
	for (j = 0, i = 14 ; s[i] != '"';)
	  back[j++] = s[i++];
      else
	show_error(1);
      if ((w->background = IMG_Load(back)) == NULL)
	show_error(5);
    }
  free(back);
}

void	scene_music(char *s, t_music *m)
{
  int	i, j;
  char	*mus;

  mus = xmalloc(512);
  memset(mus, 0, 512);
  if (!strncmp(s, "music = \"", 9))
    {
      for (j = 0, i = 9 ; s[i] != '"';)
	mus[j++] = s[i++];
      music(mus, m);
    }
  free(mus);
}

void	scene_se(char *s, t_music *m)
{
  int	i, j;
  char	*sound_e;

  sound_e = xmalloc(512);
  memset(sound_e, 0, 512);
  if (!strncmp(s, "SE \"", 4))
    {
      for (j = 0, i = 4 ; s[i] != '"';)
	sound_e[j++] = s[i++];
      se(sound_e, m);
    }
  free(sound_e);
}

typedef struct s_image_scene
{
  int	image_show;
  char	*image_name;
  SDL_Rect posImage;
  SDL_Surface *image;
} t_image_scene;

void	scene_image(char *s, t_image_scene *img_scn)
{
  int	i, j;
  char	*posImageX;
  char	*posImageY;

  posImageX = xmalloc(512);
  memset(posImageX, 0, 512);
  posImageY = xmalloc(512);
  memset(posImageY, 0, 512);
  img_scn->image_name = xmalloc(512);
  memset(img_scn->image_name, 0, 512);
  if (!strncmp(s, "image \"", 7))
    {
      img_scn->image_show = 1;
      for (j = 0, i = 7 ; s[i] != '"' ;)
	img_scn->image_name[j++] = s[i++];
      for (j = 0, i += 3 ; s[i] != ',' ;)
	posImageX[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != '"' ;)
	posImageY[j++] = s[i++];
      img_scn->posImage.x = atoi(posImageX);
      img_scn->posImage.y = atoi(posImageY);
    }
  free(posImageX);
  free(posImageY);
}

void	pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int	fd;
  char	*s;
  t_elem *e;
  char	*perso;
  char *text_save;
  t_elem_text *e_text;
  t_image_scene img_scn;

  if (m->DUCK_isPlaying == 1 && m->DUCK_TitleMusic == 1)
    {
      music_close(m);
      m->DUCK_TitleMusic = 0;
    }
  img_scn.image_show = 0;
  perso = xmalloc(512);
  memset(perso, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      DUCK_line++;
      scene_text(s, t);
      scene_show(s, l);
      scene_unshow(s, l);
      scene_background(s, w);
      scene_music(s, m);
      scene_se(s, m);
      scene_image(s, &img_scn);
      if (!strncmp(s, ">end", 4))
	clean_exit(w, m, l);
      if (!strncmp(s, ">>w", 3))
	events2(w, m, l, t, f);

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
      if (img_scn.image_show == 1)
	{
	  img_scn.image = IMG_Load(img_scn.image_name);
	  SDL_BlitSurface(img_scn.image, NULL, w->screen, &img_scn.posImage);
	}
      SDL_Flip(w->screen);
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
  DUCK_line = 0;
  printf("%sWELCOME TO %sDUCK-ENGINE%s%s ALPHA 0.1.5%s\n", "\033[04;29m", "\033[01;32m", "\033[00m", "\033[04;29m", "\033[00m");
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
  clean_exit(&w, &m, &l);
  return (0);
}
