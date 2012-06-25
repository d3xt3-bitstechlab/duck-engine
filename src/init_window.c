/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
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
  int	font_check;
  int	background_check;
  int	window_size;

  font_check = 0;
  window_size = 0;
  background_check = 0;
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
	{
	  SDL_WM_SetCaption(title, icon);
	  free(title);
	  free(icon);
	  free(back);
	  free(mus);
	  free(font);
	  if (window_size == 0)
	    show_error(12);
	  if (background_check == 0)
	    show_error(10);
	  if (font_check == 0)
	    f->size_font = 30;
	  break;
	}
      if (!strncmp(s, "WINDOW_SIZE = \"", 15))
	{
	  window_size = 1;
	  w->screen = init_window_size(w->screen, s, w);
	}
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
      if (!strncmp(s, "BACKGROUND_TITLE = \"", 20) && window_size == 1)
	{
	  background_check = 1;
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
	  font_check = 1;
	  if (s[8] != '"')
	    {
	      for (j = 0, i = 8 ; s[i] != '"';)
		f->font_used[j++] = s[i++];
	    }
	}
    }
}
