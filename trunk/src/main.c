/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Sun Jun 17 05:12:36 2012 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "get_next_line.h"
#include "xmalloc.h"
#include "list.h"
#include "text.h"
#include "header.h"

void	events2(t_window *w, t_music *m, t_list *l, t_text *t);

int sizeFont;
char *font_used;

void    show_error(int error)
{
  printf("%s!!!FATAL ERROR!!!%s\nduck-engine:%d: ", "\033[01;31m", "\033[00m", DUCK_line);
  if (error == 0)
    printf("SDL error: %s\n", SDL_GetError());
  if (error == 1)
    printf("no background title image set.\n");
  if (error == 2)
    printf("no script.duck file found.\n");
  if (error == 3)
    printf("unable to load music file.\n");
  if (error == 4)
    printf("SDL_ttf error : %s\n", TTF_GetError());
  if (error == 5)
    printf("unable to load image.\n");
  if (error == 6)
    printf("write(); has failed.\n");
  exit(0);
}

char    *limit_char(char *str, int i, int limit)
{
  int   j;
  int   k;
  char  *result;

  j = i;
  k = 0;
  result = malloc(strlen(str) + 1);
  memset(result, 0, strlen(str) + 1);
  while (str[j])
    {
      if (j == limit)
        return (result);
      result[k] = str[j];
      ++j;
      ++k;
    }
  return (result);
}

void    music(char *path, t_music *m)
{
  FMOD_System_Create(&m->system);
  FMOD_System_Init(m->system, 1, FMOD_INIT_NORMAL, NULL);
  if ((m->result = FMOD_System_CreateSound(m->system, path, FMOD_SOFTWARE
					   | FMOD_2D | FMOD_CREATESTREAM
					   | FMOD_LOOP_NORMAL, 0, &m->music)) != FMOD_OK)
    show_error(3);
  FMOD_Sound_SetLoopCount(m->music, -1);
  FMOD_System_PlaySound(m->system, FMOD_CHANNEL_FREE, m->music, 0, NULL);
  DUCK_isPlaying = 1;
}

void    music_close(t_music *m)
{
  DUCK_isPlaying = 0;
  FMOD_Sound_Release(m->music);
  FMOD_System_Close(m->system);
  FMOD_System_Release(m->system);
}

void	clean_exit(t_window *w, t_music *m, t_list *l)
{
  t_elem	*e;

  printf(" done\ncleaning...");
  e = l->head;
  while (e)
    {
      free(e->name);
      free(e->img);
      SDL_FreeSurface(e->perso);
      e = e->next;
    }
  SDL_FreeSurface(w->screen);
  SDL_FreeSurface(w->background);
  if (DUCK_isPlaying == 1)
    music_close(m);
  free(sizeX);
  free(sizeY);
  free(font_used);
  printf(" done\n");
  printf("exiting...");
  TTF_Quit();
  SDL_Quit();
  printf(" done\n");
  exit(0);
}

int	open_fd(char *str)
{
  static int fd;

  if (!fd)
    if ((fd = open(str, O_RDONLY)) < 0)
      return (-1);
  return (fd);
}

void	pars_list2(t_list *l, char *s)
{
  int	i;
  int	j;
  char	*name;
  char	*img;

  if (!strncmp(s, ">>", 2))
    {
      name = xmalloc(512);
      memset(name, 0, 512);
      img = xmalloc(512);
      memset(img, 0, 512);
      for (j = 0, i = 2 ; s[i] ;)
	{
	  if (s[i] == ' ' && s[i + 1] == '=')
	    break;
	  name[j++] = s[i++];
	}
      for (i += 4, j = 0 ; s[i] ;)
	{
	  if (s[i] == '"')
	    break;
	  img[j++] = s[i++];
	}
      ins_end_list(l, name, img);
      free(name);
      free(img);
    }
}

void	pars_list(t_list *l)
{
  int	fd;
  char	*s;

  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      DUCK_line++;
      if (!strncmp(s, ">scene", 6))
	break;
      pars_list2(l, s);
   }
}

SDL_Surface	*init_window_size(SDL_Surface *screen, char *s)
{
  int	i;
  int	j;

  sizeY = xmalloc(6);
  sizeX =  xmalloc(6);
  memset(sizeX, 0, 6);
  memset(sizeY, 0, 6);
  if (s[15] != '"')
    {
      for (j = 0, i = 15 ; s[i] != ',';)
	sizeX[j++] = s[i++];
      for (j = 0, i += 2 ; s[i] != '"';)
	sizeY[j++] = s[i++];
      if ((screen = SDL_SetVideoMode(atoi(sizeX), atoi(sizeY),
				     32, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
    }
  else
    {
      if ((screen = SDL_SetVideoMode(1000, 750, 32,
				     SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
      sizeX = strdup("1000");
      sizeY = strdup("750");
    }
  return (screen);
}

void	init_window(t_window *w, t_music *m)
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
  font_used = xmalloc(512);
  memset(font_used, 0, 512);
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      ++DUCK_line;
      if (!strncmp(s, ">caracters", 10))
	break;
      if (!strncmp(s, "WINDOW_SIZE = \"", 15))
	w->screen = init_window_size(w->screen, s);
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
	    }
	}
      if (!strncmp(s, "FONT_SIZE = \"", 13))
	{
	  if (s[13] != '"')
	    {
	      for (j = 0, i = 13 ; s[i] != '"';)
		font[j++] = s[i++];
	      sizeFont = atoi(font);
	    }
	}
      if (!strncmp(s, "FONT = \"", 8))
	{
	  if (s[8] != '"')
	    {
	      for (j = 0, i = 8 ; s[i] != '"';)
		font_used[j++] = s[i++];
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

void	text_module(char *text, t_window *w, TTF_Font *font, SDL_Rect posText)
{
  unsigned int i = 2;
  int height, width;
  int size_saved;
  int size_init = 0;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;

  size_saved = 0;
  while (i < strlen(text))
    {
      size_init = size_saved;
      i = size_saved + 2;
      width = 0;
      while (text[i])
        {
          TTF_SizeText(font, limit_char(text, size_init, i), &width, &height);
          if (width > atoi(sizeX))
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
        posText.y += height + 3;
      texte = TTF_RenderText_Blended(font, limit_char(text, size_init, size_saved),
				     white_color);
      SDL_BlitSurface(texte, NULL, w->screen, &posText);
      SDL_Flip(w->screen);
      i += 2;
    }
}

void	pars_scene(t_window *w, t_music *m, t_list *l, t_text *t)
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
  SDL_Surface *text_support;

  TTF_Font *font = NULL;
  SDL_Rect posText;
  posText.x = 15;
  posText.y = 15;

  if ((font = TTF_OpenFont(/*"fonts/designosaur-regular.ttf"*/font_used, sizeFont)) == NULL)
    show_error(4);

  text_support = SDL_CreateRGBSurface(SDL_HWSURFACE, atoi(sizeX), atoi(sizeY),
				      32, 0, 0, 0, 0);

  e = l->head;
  while (e)
    {
      printf("HELLO %d\n", e->is_show);
      e = e->next;
    }

  if (DUCK_isPlaying == 1)
    music_close(m);
  back = xmalloc(512);
  memset(back, 0, 512);
  mus = xmalloc(512);
  memset(mus, 0, 512);
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
      /*if (!strncmp(s, ">end", 4))
	break;*/
      if (!strncmp(s, "background = \"", 14))
	{
	  if (s[14] != '"')
	    {
	      for (j = 0, i = 14 ; s[i] != '"';)
		back[j++] = s[i++];
	      w->background = IMG_Load(back);
	      /*SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
		SDL_Flip(w->screen);*/
	    }
	  else
	    show_error(4);
	}
      if (!strncmp(s, "music = \"", 9))
	{
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

		  /*SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
		    SDL_Flip(w->screen);*/
		}
	      e = e->next;
	    }
	}
      if (!strncmp(s, "<", 1))
	{
	  /*SDL_SetAlpha(text_support, SDL_SRCALPHA, 100);
	  SDL_BlitSurface(text_support, NULL, w->screen, &w->posBack);
	  SDL_Flip(w->screen);*/
	  text = xmalloc(4096);
	  memset(text, 0, 4096);

	  for (j = 0, i = 1 ; s[i] != '/' && s[i + 1] != '>';)
	    text[j++] = s[i++];
	  
	  ins_end_list_text(t, text);
	  /*text_module(text, w, font, posText);*/

	  /*texte = TTF_RenderText_Blended(font, text, white_color);
	  SDL_BlitSurface(texte, NULL, w->screen, &posText);
	  SDL_Flip(w->screen);*/
	}
      if (!strncmp(s, ">end", 4))
	clean_exit(w, m, l);
      if (!strncmp(s, ">>w", 3))
	events2(w, m, l, t);

      /* bliter background, ecran, et dernier texte ! */
      SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
      /* SDL_Flip(w->screen); */

      SDL_SetAlpha(text_support, SDL_SRCALPHA, 100);
      SDL_BlitSurface(text_support, NULL, w->screen, &w->posBack);
      /* SDL_Flip(w->screen); */

      show_list(l);
      show_list_text(t);
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
	  t_elem_text *e_text;
	  char *text_save;
	  text_save = xmalloc(4096);
	  memset(text_save, 0, 4096);
	  e_text = t->tail;
	  text_save = strdup(e_text->data);
	  text_module(text_save, w, font, posText);
	}
    }
}

void	events2(t_window *w, t_music *m, t_list *l, t_text *t)
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
	      pars_scene(w, m, l, t);
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

void	events(t_window *w, t_music *m, t_list *l, t_text *t)
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
	      pars_scene(w, m, l, t);
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

void	init_zeroes(t_list *l)
{
  t_elem *e;

  e = l->head;
  while (e)
    {
      printf("\n>>>>> %s\n", e->name);
      e->is_show = 0;
      e = e->next;
    }
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  t_list l;
  t_text t;
  t_window w;
  t_music m;

  w.screen = NULL;
  w.background = NULL;
  printf("%sWELCOME TO %sDUCK-ENGINE%s%s ALPHA 0.0.7%s\n", "\033[04;29m", "\033[01;32m", "\033[00m", "\033[04;29m", "\033[00m");
  printf("initialiazing SDL... ");
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  printf("done\n");
  printf("initialiazing SDL_ttf... ");
  if (TTF_Init() == -1)
    show_error(4);
  printf("done\n");
  printf("initialiazing window parameters... ");
  init_window(&w, &m);
  printf("done\n");
  init_list(&l);
  printf("parsing caracter list... ");
  pars_list(&l);
  show_list(&l);
  init_zeroes(&l);
  printf("done\n");
  init_list_text(&t);
  if ((write(1, "showing window...", 17)) == -1)
    show_error(6);
  events(&w, &m, &l, &t);
  clean_exit(&w, &m, &l);
  return (0);
}
