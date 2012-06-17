/*
** header.h for  in /home/marcha_r/Dropbox/perso/duck-engine
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun 13 16:38:31 2012 
** Last update Wed Jun 13 17:02:37 2012 
*/

#ifndef __DUCK_ENGINE__
#define __DUCK_ENGINE__

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

int	DUCK_line = 0;
char    *sizeX;
char    *sizeY;
int	DUCK_isPlaying = 0;

void	show_error(int error);

#endif
