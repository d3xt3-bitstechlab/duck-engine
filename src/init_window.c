/*
** init_window.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Mon Jun 18 10:44:44 2012 
** Last update Mon Jun 18 18:52:42 2012 
*/

#include "header.h"
#include "get_next_line.h"

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
      if (!strncmp(s, ">characters", 11))
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
	  for (j = 0, i = 15 ; s[i] != '"';)
	    icon[j++] = s[i++];
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
	  for (j = 0, i = 15 ; s[i] != '"';)
	    mus[j++] = s[i++];
	  music(mus, m);
	  m->DUCK_TitleMusic = 1;
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
