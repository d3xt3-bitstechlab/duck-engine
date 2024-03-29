/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"
#include "fmodex/fmod.h"

/***

this plays music.
I use fmod, if you ask me.

***/

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

/***

here you pause the music.
...boy, was it worth the commentary ?...

***/

void    music_pause(t_music *m)
{
  FMOD_CHANNELGROUP *channel;
  FMOD_BOOL state;

  if (m->DUCK_isPlaying == 1)
    {
      FMOD_System_GetMasterChannelGroup(m->system, &channel);
      FMOD_ChannelGroup_GetPaused(channel, &state);
      if (state)
        FMOD_ChannelGroup_SetPaused(channel, 0);
      else
        FMOD_ChannelGroup_SetPaused(channel, 1);
    }
}

void    music_close(t_music *m)
{
  m->DUCK_isPlaying = 0;
  FMOD_Sound_Release(m->music);
  FMOD_System_Close(m->system);
  FMOD_System_Release(m->system);
}

/***

sound effects! hallelujah!
it's super glitchy and still not corrected!

***/

void    se(char *path, t_music *m)
{
  FMOD_System_Create(&m->system);
  FMOD_System_Init(m->system, 1, FMOD_INIT_NORMAL, NULL);
  if ((m->result = FMOD_System_CreateSound(m->system, path, FMOD_SOFTWARE
					   | FMOD_2D | FMOD_CREATESTREAM
					   | FMOD_LOOP_NORMAL, 0, &m->music)) != FMOD_OK)
    show_error(3);
  FMOD_Sound_SetLoopCount(m->music, 0);
  FMOD_System_PlaySound(m->system, FMOD_CHANNEL_FREE, m->music, 0, NULL);
}
