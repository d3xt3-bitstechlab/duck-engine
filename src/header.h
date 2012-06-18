/*
** header.h for  in /home/marcha_r/Dropbox/perso/duck-engine
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun 13 16:38:31 2012 
** Last update Mon Jun 18 14:42:47 2012 
*/

#ifndef __DUCK_ENGINE__
#define __DUCK_ENGINE__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "list.h"
#include "text.h"

typedef struct s_window
{
  SDL_Surface *screen;
  SDL_Surface *background;
  SDL_Rect posBack;
  char    *sizeX;
  char    *sizeY;
} t_window;

typedef struct s_music
{
  FMOD_SYSTEM   *system;
  FMOD_SOUND    *music;
  FMOD_RESULT   result;
  int	DUCK_isPlaying;
  int	DUCK_TitleMusic;
} t_music;

typedef struct s_font
{
  TTF_Font *font;
  int	size_font;
  char	*font_used;
  SDL_Rect posText;
  SDL_Surface *text_support;
} t_font;

int	DUCK_line;

int	open_fd(char *str);
void	pars_list(t_list *l);
void	show_error(int error);
void	init_zeroes(t_list *l);
void	music_pause(t_music *m);
void	music_close(t_music *m);
void	music(char *path, t_music *m);
char	*limit_char(char *str, int i, int limit);
void	clean_exit(t_window *w, t_music *m, t_list *l);
void    text_module(char *text, t_window *w, t_font *f);
void	init_window(t_window *w, t_music *m, t_font *f);
SDL_Surface *init_window_size(SDL_Surface *screen, char *s, t_window *w);
void    events(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);
void    events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);
void    pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);

#endif
