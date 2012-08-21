/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"

/***

parsing text and putting it into
it's linked list. well, it's shitty
parsing, no, it's not even parsing...

***/

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

/***

this function basically shows the caracters
that is called by the script.duck file...

***/

void	scene_show(char *s, t_list *l)
{
  t_elem *e;
  int	i, j;
  char	*show;
  int	exists;
  char	*posPersoX;
  char	*posPersoY;

  exists = 0;
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
	      exists = 1;
	      e->pos.x = atoi(posPersoX);
	      e->pos.y = atoi(posPersoY);
	      e->is_show = 1;
	    }
	  e = e->next;
	}
      if (exists == 0)
	show_error(7);
    }
  free(show);
  free(posPersoX);
  free(posPersoY);
}

/***

and this one unshow it!
I'm a genius.

***/

void	scene_unshow(char *s, t_list *l)
{
  int	i, j;
  int	exists;
  char	*unshow;
  t_elem *e;

  exists = 0;
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
	    {
	      exists = 1;
	      e->is_show = 0;
	    }
	  e = e->next;
	}
      if (exists == 0)
	show_error(8);
    }
  free(unshow);
}

/***

background in the scene?
it shall appear!

***/

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

/***

the same thing for the music...

***/

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

/***

and the sound effects...

***/

void	scene_se(char *s, t_music *m)
{
  int	i, j;
  char	*sound_e;

  sound_e = xmalloc(512);
  memset(sound_e, 0, 512);
  if (!strncmp(s, "sound \"", 7))
    {
      for (j = 0, i = 7 ; s[i] != '"';)
	sound_e[j++] = s[i++];
      se(sound_e, m);
    }
  free(sound_e);
}

/***

and the images...

***/

void	scene_image(char *s, t_image *img)
{
  int	i, j;
  char	*posImageX;
  char	*posImageY;
  char	*image;

  posImageX = xmalloc(512);
  memset(posImageX, 0, 512);
  posImageY = xmalloc(512);
  memset(posImageY, 0, 512);
  image = xmalloc(512);
  memset(image, 0, 512);
  if (!strncmp(s, "image \"", 7))
    {
      img->image_show = 1;
      for (j = 0, i = 7 ; s[i] != '"' ;)
	image[j++] = s[i++];
      for (j = 0, i += 3 ; s[i] != ',' ;)
	posImageX[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != '"' ;)
	posImageY[j++] = s[i++];
      img->posImage.x = atoi(posImageX);
      img->posImage.y = atoi(posImageY);
      img->image_name = strdup(image);
    }
  free(posImageX);
  free(posImageY);
  free(image);
}
