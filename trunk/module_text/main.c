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
  int	j;
  int	k;
  char	*result;

  j = i;
  k = 0;
  result = malloc(strlen(str) + 1);
  memset(result, 0, strlen(str) + 1);
  while (str[j])
    {
      if (j == limit)
	return (result);
      result[k] = str[j];
      ++j;
      ++k;
    }
  return (result);
}

int main(int argc, char *argv[])
{
  SDL_Surface *ecran = NULL, *imageDeFond = NULL;
  SDL_Rect positionFond, positionSapin; 
  TTF_Font *font = NULL;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;
  SDL_Rect posText;
  char	*text = malloc(4096);

  int size_init = 0;
  int size_saved;
  int i = 2;

  positionFond.x = 0;
  positionFond.y = 0;
  posText.x = 15;
  posText.y = 15;
  memset(text, 0, 4096);
  text = strdup("Coucou texte trop long il faut qu'il le soit. Aujourd'hui j'ai mange du pain grille avec du nutella, je dois vous dire que c'est vraiment tres bon. Bon, c'est sur que c'est pas tres interessant, mais on s'en fout pas mal, je fais que tester. Est-ce que ca marche bien ? Je me demande en ecrivant ce texte.");
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("DUCK-ENGINE: text_module test", NULL);
  imageDeFond = IMG_Load("../graph/scene.jpg");
  SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
  SDL_Flip(ecran);
  font = TTF_OpenFont("../fonts/designosaur-regular.ttf", 30);

  while (i < strlen(text))
    {
      size_init = size_saved;
      i = size_saved + 2;
      w = 0;
      while (text[i])
	{
	  TTF_SizeText(font, limit_char(text, size_init, i), &w, &h);
	  if (w > sizeX)
	    {
	      size_saved = i - 3;
	      break;
	    }
	  if (text[i + 1] == '\0')
	    {
	      size_saved = i + 1;
	      break;
	    }
	  ++i;
	}
      if (size_init > 0)
	posText.y += h + 3;
      texte = TTF_RenderText_Blended(font, limit_char(text, size_init, size_saved), white_color);
      SDL_BlitSurface(texte, NULL, ecran, &posText);
      SDL_Flip(ecran);
      i += 2;
    }
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
