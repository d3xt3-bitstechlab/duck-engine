/*
** main.c for  in /home/marcha_r/Dropbox/perso/duck-engine/src
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun  6 01:53:48 2012 
** Last update Sun Jun 10 17:10:29 2012 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"

void	events()
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
	    default:
	      break;
            }
	  break;
	default:
	  break;
	}
    }
}

typedef struct s_music
{
  FMOD_SYSTEM   *system;
  FMOD_SOUND    *music;
  FMOD_RESULT   result;
} t_music;

void    music(char *path, t_music *m)
{
  FMOD_System_Create(&m->system);
  FMOD_System_Init(m->system, 1, FMOD_INIT_NORMAL, NULL);
  m->result = FMOD_System_CreateSound(m->system, path, FMOD_SOFTWARE
                                      | FMOD_2D | FMOD_CREATESTREAM, 0, &m->music);
  if (m->result != FMOD_OK)
    printf("unable to load music file.\n");
  FMOD_Sound_SetLoopCount(m->music, -1);
  FMOD_System_PlaySound(m->system, FMOD_CHANNEL_FREE, m->music, 0, NULL);
}

void    music_close(t_music *m)
{
  FMOD_Sound_Release(m->music);
  FMOD_System_Release(m->system);
  FMOD_System_Close(m->system);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  t_music m;

  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) == -1)
    printf("SDL error: %s\n", SDL_GetError());
  music("all.mp3", &m);
  events();
  music_close(&m);
  SDL_Quit();
  return (0);
}
