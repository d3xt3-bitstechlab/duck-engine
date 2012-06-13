#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
 
void pause();

int sizeX = 800;
int sizeY = 600;

int main(int argc, char *argv[])
{
  SDL_Surface *ecran = NULL, *imageDeFond = NULL, *sapin = NULL;
  SDL_Rect positionFond, positionSapin; 
  TTF_Font *font = NULL;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;
  SDL_Rect posText;
  char	*text = malloc(512);

  positionFond.x = 0;
  positionFond.y = 0;
  posText.x = 15;
  posText.y = 15;
  text = strdup("Coucou je suis un nazi et je teste le super module de texte que je suis en train de coder pour Duck-Engine!");

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("DUCK-ENGINE: text_module test", NULL);
  imageDeFond = IMG_Load("../graph/scene.jpg");
  SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
  SDL_Flip(ecran);
  font = TTF_OpenFont("../fonts/designosaur-regular.ttf", 30);
  texte = TTF_RenderText_Blended(font, text, white_color);
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
