/*
** show_error.c for  in /home/marcha_r/Dropbox/perso/duck-engine
** 
** Made by 
** Login   <marcha_r@epitech.net>
** 
** Started on  Wed Jun 13 16:43:58 2012 
** Last update Wed Jun 13 17:02:43 2012 
*/

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "header.h"

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

