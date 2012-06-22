/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
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

typedef struct s_image
{
  int	image_show;
  char	*image_name;
  SDL_Rect posImage;
  SDL_Surface *image;
} t_image;

int	DUCK_line;

int	open_fd(char *str);
void	pars_list(t_list *l);
void	show_error(int error);
void	init_zeroes(t_list *l);
void    text_history(t_text *t);
void	music_pause(t_music *m);
void	music_close(t_music *m);
void    se(char *path, t_music *m);
void	music(char *path, t_music *m);
char	*limit_char(char *str, int i, int limit);
void	clean_exit(t_window *w, t_music *m, t_list *l, t_text *t);
void    text_module(char *text, t_window *w, t_font *f);
void	init_window(t_window *w, t_music *m, t_font *f);
SDL_Surface *init_window_size(SDL_Surface *screen, char *s, t_window *w);
void    events(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);
void    events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img);
void    refresh(t_window *w, t_list *l, t_text *t, t_font *f, t_image *img);
void    pars_scene(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f);
void	history_navigation(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img);

void	scene_text(char *s, t_text *t);
void	scene_show(char *s, t_list *l);
void	scene_unshow(char *s, t_list *l);
void	scene_background(char *s, t_window *w);
void	scene_music(char *s, t_music *m);
void	scene_se(char *s, t_music *m);
void	scene_image(char *s, t_image *img);

#endif
