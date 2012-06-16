#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
 
void pause();

int sizeX = 800;
int sizeY = 600;
int w, h;

char	*limit_char(char *str, int i, int limit)
{
  char	*result;

  result = malloc(strlen(str) + 1);
  memset(result, 0, strlen(str) + 1);
  while (str[i])
    {
      if (i == limit)
	return (result);
      result[i] = str[i];
      ++i;
    }
  return (result);
}

int main(int argc, char *argv[])
{
  SDL_Surface *ecran = NULL, *imageDeFond = NULL, *sapin = NULL;
  SDL_Rect positionFond, positionSapin; 
  TTF_Font *font = NULL;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;
  SDL_Rect posText;
  char	*text = malloc(4096);

  positionFond.x = 0;
  positionFond.y = 0;
  posText.x = 15;
  posText.y = 15;
  memset(text, 0, 4096);
  text = strdup("Coucou texte trop long il faut qu'il le soit... C'est pour le bien de l'humanite, tu comprends?");
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("DUCK-ENGINE: text_module test", NULL);
  imageDeFond = IMG_Load("../graph/scene.jpg");
  SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
  SDL_Flip(ecran);
  font = TTF_OpenFont("../fonts/designosaur-regular.ttf", 30);

  int size_init = 0;
  int size_saved;
  int i = 2;
  while (text[i])
    {
      limit_char(text, 0, i);
      TTF_SizeText(font, limit_char(text, 0, i), &w, &h);
      if (w > sizeX)
	{
	  size_saved = i - 3;
	  break;
	}
      ++i;
    }

  printf("WINDOW_SIZE: %d*%d\n", sizeX, sizeY);
  if (TTF_SizeText(font, "m", &w, &h))
    printf("lol\n");
  else
    printf("width=%d height=%d\n", w, h);
  printf("size_saved : %d\n", size_saved);

  texte = TTF_RenderText_Blended(font, limit_char(text, 0, size_saved), white_color);
  SDL_BlitSurface(texte, NULL, ecran, &posText);
  SDL_Flip(ecran);

  pause();
 
  SDL_Quit();
  TTF_Quit();
  return EXIT_SUCCESS;
}
 
void pause()
{
  int continuer = 1;
  SDL_Event event;
 
  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = 0;
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
