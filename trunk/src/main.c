/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Mon Jun 18 10:51:16 2012 
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

void	pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  t_elem *e;
  char	*back;
  char	*mus;
  char	*perso;
  char	*show;
  char	*text;
  char	*posPersoX;
  char	*posPersoY;
  t_elem_text *e_text;
  char *text_save;

  if (m->DUCK_isPlaying == 1 && m->DUCK_TitleMusic == 1)
    {
      music_close(m);
      m->DUCK_TitleMusic = 0;
    }
  back = xmalloc(512);
  memset(back, 0, 512);
  perso = xmalloc(512);
  memset(perso, 0, 512);
  text = xmalloc(4096);
  memset(text, 0, 4096);
  posPersoX = xmalloc(512);
  memset(posPersoX, 0, 512);
  posPersoY = xmalloc(512);
  memset(posPersoY, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      DUCK_line++;
      if (!strncmp(s, "background = \"", 14))
	{
	  if (s[14] != '"')
	    {
	      for (j = 0, i = 14 ; s[i] != '"';)
		back[j++] = s[i++];
	      w->background = IMG_Load(back);
	    }
	  else
	    show_error(4);
	}
      if (!strncmp(s, "music = \"", 9))
	{
	  mus = xmalloc(512);
	  memset(mus, 0, 512);
	  if (s[9] != '"')
	    {
	      for (j = 0, i = 9 ; s[i] != '"';)
		mus[j++] = s[i++];
	      music(mus, m);
	    }
	}
      if (!strncmp(s, "show ", 5))
	{
	  show = xmalloc(512);
	  memset(show, 0, 512);
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
      if (!strncmp(s, "<", 1))
	{
	  text = xmalloc(4096);
	  memset(text, 0, 4096);
	  for (j = 0, i = 1 ; s[i] != '/' && s[i + 1] != '>';)
	    text[j++] = s[i++];
	  ins_end_list_text(t, text);
	}
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
	    {
	      SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
	      SDL_Flip(w->screen);
	    }
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
  printf("%sWELCOME TO %sDUCK-ENGINE%s%s ALPHA 0.1%s\n", "\033[04;29m", "\033[01;32m", "\033[00m", "\033[04;29m", "\033[00m");
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
