/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Tue Jun 12 17:29:17 2012 
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

typedef struct s_window
{
  SDL_Surface *screen;
  SDL_Surface *background;
  SDL_Rect posBack;
} t_window;

typedef struct s_music
{
  FMOD_SYSTEM   *system;
  FMOD_SOUND    *music;
  FMOD_RESULT   result;
} t_music;

int	line = 0;
char	*sizeX;
char	*sizeY;
int	isPlaying = 0;

void	show_error(int error)
{
  printf("%s!!!FATAL ERROR!!!%s\nduck-engine:%d: ", "\033[01;31m", "\033[00m", line);
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
  exit(0);
}

void    music(char *path, t_music *m)
{
  FMOD_System_Create(&m->system);
  FMOD_System_Init(m->system, 1, FMOD_INIT_NORMAL, NULL);
  m->result = FMOD_System_CreateSound(m->system, path, FMOD_SOFTWARE
                                      | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &m->music);
  if (m->result != FMOD_OK)
    show_error(3);
  FMOD_Sound_SetLoopCount(m->music, -1);
  FMOD_System_PlaySound(m->system, FMOD_CHANNEL_FREE, m->music, 0, NULL);
  isPlaying = 1;
}

void    music_close(t_music *m)
{
  isPlaying = 0;
  FMOD_Sound_Release(m->music);
  FMOD_System_Close(m->system);
  FMOD_System_Release(m->system);
}

void	clean_exit(t_window *w, t_music *m, t_list *l)
{
  t_elem	*e;

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
  if (isPlaying == 1)
    music_close(m);
  free(sizeX);
  free(sizeY);
  TTF_Quit();
  SDL_Quit();
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

void	pars_list(t_list *l)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*name;
  char	*img;

  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      line++;
      if (!strncmp(s, ">scene", 6))
	break;
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
	  i += 4;
	  for (j = 0 ; s[i] ;)
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
}

SDL_Surface	*init_window_size(SDL_Surface *screen, char *s)
{
  int	i;
  int	j;

  sizeY = xmalloc(6);
  sizeX =  xmalloc(6);
  memset(sizeX, 0, 6);
  memset(sizeY, 0, 6);
  if (s[16] != '"')
    {
      for (j = 0, i = 15 ; s[i] != ',';)
	sizeX[j++] = s[i++];
      for (j = 0, i +=2 ; s[i] != '"';)
	sizeY[j++] = s[i++];
      if ((screen = SDL_SetVideoMode(atoi(sizeX), atoi(sizeY),
				     32, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
	show_error(0);
    }
  else
    if ((screen = SDL_SetVideoMode(1000, 750, 32,
				   SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
      show_error(0);
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
  if ((fd = open_fd("script.duck")) == -1)
    show_error(2);
  while ((s = get_next_line(fd)))
    {
      ++line;
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
    }
  SDL_WM_SetCaption(title, icon);
  free(title);
  free(icon);
  free(back);
  free(mus);
}

void	events2(t_window *w, t_music *m, t_list *l)
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

void	pars_scene(t_window *w, t_music *m, t_list *l)
{
  int	i;
  int	j;
  int	fd;
  char	*s;
  char	*back;
  char	*mus;
  char	*perso;
  char	*show;
  char	*text;
  char	*posPersoX;
  char	*posPersoY;
  t_elem *e;
  SDL_Surface *text_support;

  TTF_Font *police = NULL;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;

  SDL_Rect posText;

  posText.x = 15;
  posText.y = 15;
  
  police = TTF_OpenFont("fonts/designosaur-regular.ttf", 30);

  if (isPlaying == 1)
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
  text_support = SDL_CreateRGBSurface(SDL_HWSURFACE, atoi(sizeX), atoi(sizeY),
				      32, 0, 0, 0, 0);
  SDL_SetAlpha(text_support, SDL_SRCALPHA, 100);
  SDL_BlitSurface(text_support, NULL, w->screen, &w->posBack);
  SDL_Flip(w->screen);
  while ((s = get_next_line(fd)))
    {
      line++;
      if (!strncmp(s, ">end", 4))
	break;
      else if (!strncmp(s, "background = \"", 14))
	{
	  if (s[14] != '"')
	    {
	      for (j = 0, i = 14 ; s[i] != '"';)
		back[j++] = s[i++];
	      w->background = IMG_Load(back);
	      SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);
	      SDL_Flip(w->screen);
	    }
	  else
	    show_error(4);
	}
      else if (!strncmp(s, "music = \"", 9))
	{
	  if (s[9] != '"')
	    {
	      for (j = 0, i = 9 ; s[i] != '"';)
		mus[j++] = s[i++];
	      music(mus, m);
	    }
	}
      else if (!strncmp(s, "show ", 5))
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
		  SDL_BlitSurface(e->perso, NULL, w->screen, &e->pos);
		  SDL_Flip(w->screen);
		}
	      e = e->next;
	    }
	}
      else if (!strncmp(s, "<", 1))
	{
	  for (j = 0, i = 1 ; s[i] != '/' && s[i + 1] != '>';)
	    text[j++] = s[i++];
	  texte = TTF_RenderText_Blended(police, text, white_color);
	  SDL_BlitSurface(texte, NULL, w->screen, &posText);
	  SDL_Flip(w->screen);
	}
    }
  events2(w, m, l);
}

void	events(t_window *w, t_music *m, t_list *l)
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
	      pars_scene(w, m, l);
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
  t_window w;
  t_music m;

  w.screen = NULL;
  w.background = NULL;
  printf("duck-engine: initialiazing SDL... ");
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    show_error(0);
  printf("done\n");
  printf("duck-engine: initialiazing SDL_ttf... ");
  if (TTF_Init() == -1)
    show_error(4);
  printf("done\n");
  printf("duck-engine: initialiazing window parameters... ");
  init_window(&w, &m);
  printf("done\n");
  init_list(&l);
  printf("duck-engine: parsing caracter list... ");
  pars_list(&l);
  printf("done\n");
  printf("duck-engine: showing window...\n");
  events(&w, &m, &l);
  clean_exit(&w, &m, &l);
  return (0);
}
