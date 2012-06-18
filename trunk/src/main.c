/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Mon Jun 18 10:42:58 2012 
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

void	events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);

void	init_window(t_window *w, t_music *m, t_font *f)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*title;
  char	*icon;
  char	*back;
  char	*mus;
  char	*font;

  w->posBack.x = 0;
  w->posBack.y = 0;
  title = xmalloc(512);
  memset(title, 0, 512);
  icon = xmalloc(512);
  memset(icon, 0, 512);
  back = xmalloc(512);
  memset(back, 0, 512);
  mus = xmalloc(512);
  memset(mus, 0, 512);
  font = xmalloc(512);
  memset(font, 0, 512);
  f->font_used = xmalloc(512);
  memset(f->font_used, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      ++DUCK_line;
      if (!strncmp(s, ">caracters", 10))
	break;
      if (!strncmp(s, "WINDOW_SIZE = \"", 15))
	w->screen = init_window_size(w->screen, s, w);
      if (!strncmp(s, "WINDOW_TITLE = \"", 16))
	{
	  if (s[16] != '"')
	    for (j = 0, i = 16 ; s[i] != '"';)
	      title[j++] = s[i++];
	  else
	    title = strdup("Duck-Engine : visual novel creator");
	}
      if (!strncmp(s, "WINDOW_ICON = \"", 15))
	{
	  if (s[15] != '"')
	    for (j = 0, i = 15 ; s[i] != '"';)
	      icon[j++] = s[i++];
	  else
	    icon = strdup(".duck-graph/icon.png");
	}
      if (!strncmp(s, "BACKGROUND_TITLE = \"", 20))
	{
	  if (s[20] != '"')
	    for (j = 0, i = 20 ; s[i] != '"';)
	      back[j++] = s[i++];
	  else
	    show_error(1);
	  if ((w->background = IMG_Load(back)) == NULL)
	    show_error(5);
	  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
	  SDL_Flip(w->screen);
	}
      if (!strncmp(s, "MUSIC_TITLE = \"", 15))
	{
	  if (s[15] != '"')
	    {
	      for (j = 0, i = 15 ; s[i] != '"';)
		mus[j++] = s[i++];
	      music(mus, m);
	      m->DUCK_TitleMusic = 1;
	    }
	}
      if (!strncmp(s, "FONT_SIZE = \"", 13))
	{
	  if (s[13] != '"')
	    {
	      for (j = 0, i = 13 ; s[i] != '"';)
		font[j++] = s[i++];
	      f->size_font = atoi(font);
	    }
	}
      if (!strncmp(s, "FONT = \"", 8))
	{
	  if (s[8] != '"')
	    {
	      for (j = 0, i = 8 ; s[i] != '"';)
		f->font_used[j++] = s[i++];
	    }
	}
    }
  SDL_WM_SetCaption(title, icon);
  free(title);
  free(icon);
  free(back);
  free(mus);
  free(font);
}

void	text_module(char *text, t_window *w, t_font *f)
{
  unsigned int i = 2;
  int height, width;
  int size_saved;
  int size_init = 0;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;

  f->posText.x = 15;
  f->posText.y = 15;
  size_saved = 0;
  while (i < strlen(text))
    {
      size_init = size_saved;
      i = size_saved + 2;
      width = 0;
      while (text[i])
        {
          TTF_SizeText(f->font, limit_char(text, size_init, i), &width, &height);
          if (width > atoi(w->sizeX))
            {
              size_saved = i - 3;
              break;
            }
          if (text[i + 1] == '\0')
            {
              size_saved = i + 1;
              break;
            }
          ++i;
        }
      if (size_init > 0)
        f->posText.y += height + 3;
      texte = TTF_RenderText_Blended(f->font, limit_char(text, size_init, size_saved),
				     white_color);
      SDL_BlitSurface(texte, NULL, w->screen, &f->posText);
      SDL_Flip(w->screen);
      i += 2;
    }
}

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
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_RETURN:
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
