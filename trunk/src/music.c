/*
** music.c for  in /home/marcha_r/Dropbox/perso/duck-engine
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Sun Jun 17 17:33:36 2012 
** Last update Mon Jun 18 11:28:34 2012 
*/

#include "header.h"
#include "fmodex/fmod.h"

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
  m->DUCK_isPlaying = 1;
}

void	music_pause(t_music *m)
{

}

void    music_close(t_music *m)
{
  m->DUCK_isPlaying = 0;
  FMOD_Sound_Release(m->music);
  FMOD_System_Close(m->system);
  FMOD_System_Release(m->system);
}
