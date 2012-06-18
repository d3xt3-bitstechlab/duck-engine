/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"

void	text_module(char *text, t_window *w, t_font *f)
{
  unsigned int i = 2;
  int height, width;
  int size_saved;
  int size_init = 0;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;

  f->posText.x = 15;
  f->posText.y = 15;
  size_saved = 0;
  while (i < strlen(text))
    {
      size_init = size_saved;
      i = size_saved + 2;
      width = 0;
      while (text[i])
        {
          TTF_SizeText(f->font, limit_char(text, size_init, i), &width, &height);
          if (width > atoi(w->sizeX))
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
        f->posText.y += height + 3;
      texte = TTF_RenderText_Blended(f->font, limit_char(text, size_init, size_saved),
				     white_color);
      SDL_BlitSurface(texte, NULL, w->screen, &f->posText);
      i += 2;
    }
}
