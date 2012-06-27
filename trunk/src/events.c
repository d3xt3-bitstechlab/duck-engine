/*
** DUCK-ENGINE
** Made by theo marchal
** http://code.google.com/p/duck-engine/
*/

#include "header.h"
#include "text.h"

/*
  N = longueur rectangle noir
  T = taille (longueur texte)
  C = (N - T) / 2
*/

void	game_menu(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img)
{
  int	next;
  int height, width;
  SDL_Event event;
  SDL_Rect posBox;
  SDL_Surface *menu_box;
  SDL_Color white_color = {255,255,255,255};
  SDL_Surface *texte = NULL;
  TTF_Font *font;

  next = 1;
  posBox.x = (atoi(w->sizeX) - atoi(w->sizeX) / 2.5) / 2;
  posBox.y = atoi(w->sizeY) / 20;

  if ((font = TTF_OpenFont(f->font_used, f->size_font + 10)) == NULL)
    show_error(4);

  f->posText.x = atoi(w->sizeX) / 2.2;
  f->posText.y = atoi(w->sizeY) / 4.48;
  menu_box = SDL_CreateRGBSurface(SDL_HWSURFACE, atoi(w->sizeX) / 2.5,
				  atoi(w->sizeY) / 10, 32, 0, 0, 0, 0);
  SDL_FillRect(menu_box, NULL, SDL_MapRGB(w->screen->format, 0, 0, 0));
  SDL_BlitSurface(w->background, NULL, w->screen, &w->posBack);

  posBox.y += atoi(w->sizeY) / 7;
  TTF_SizeText(font, "SAVE", &width, &height);
  f->posText.x = ((atoi(w->sizeX) + (atoi(w->sizeX) / 2.5)) - (width + (atoi(w->sizeX) / 2.5))) / 2;
  SDL_BlitSurface(menu_box, NULL, w->screen, &posBox);
  texte = TTF_RenderText_Blended(font, "SAVE", white_color);
  SDL_BlitSurface(texte, NULL, w->screen, &f->posText);

  posBox.y += atoi(w->sizeY) / 7;
  f->posText.y += atoi(w->sizeY) / 7;
  TTF_SizeText(font, "LOAD GAME", &width, &height);
  f->posText.x = ((atoi(w->sizeX) + (atoi(w->sizeX) / 2.5)) - (width + (atoi(w->sizeX) / 2.5))) / 2;
  SDL_BlitSurface(menu_box, NULL, w->screen, &posBox);
  texte = TTF_RenderText_Blended(font, "LOAD GAME", white_color);
  SDL_BlitSurface(texte, NULL, w->screen, &f->posText);

  posBox.y += atoi(w->sizeY) / 7;
  f->posText.y += atoi(w->sizeY) / 7;
  TTF_SizeText(font, "SOUND", &width, &height);
  f->posText.x = ((atoi(w->sizeX) + (atoi(w->sizeX) / 2.5)) - (width + (atoi(w->sizeX) / 2.5))) / 2;
  SDL_BlitSurface(menu_box, NULL, w->screen, &posBox);
  texte = TTF_RenderText_Blended(font, "SOUND", white_color);
  SDL_BlitSurface(texte, NULL, w->screen, &f->posText);

  posBox.y += atoi(w->sizeY) / 7;
  f->posText.y += atoi(w->sizeY) / 7;
  TTF_SizeText(font, "GRAPHICS", &width, &height);
  f->posText.x = ((atoi(w->sizeX) + (atoi(w->sizeX) / 2.5)) - (width + (atoi(w->sizeX) / 2.5))) / 2;
  SDL_BlitSurface(menu_box, NULL, w->screen, &posBox);
  texte = TTF_RenderText_Blended(font, "GRAPHICS", white_color);
  SDL_BlitSurface(texte, NULL, w->screen, &f->posText);

  posBox.y += atoi(w->sizeY) / 7;
  f->posText.y += atoi(w->sizeY) / 7;
  TTF_SizeText(font, "QUIT GAME", &width, &height);
  f->posText.x = ((atoi(w->sizeX) + (atoi(w->sizeX) / 2.5)) - (width + (atoi(w->sizeX) / 2.5))) / 2;
  SDL_BlitSurface(menu_box, NULL, w->screen, &posBox);
  texte = TTF_RenderText_Blended(font, "QUIT GAME", white_color);
  SDL_BlitSurface(texte, NULL, w->screen, &f->posText);

  SDL_SetAlpha(f->text_support, SDL_SRCALPHA, 100);
  SDL_Flip(w->screen);
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  clean_exit(w, m, l, t);
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    events2(w, m, l, t, f, img);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_RETURN:
	      break;
	    case SDLK_SPACE:
	      break;
	    case SDLK_DOWN:
	      break;
	    case SDLK_UP:
	      break;
	    case SDLK_ESCAPE:
	      events2(w, m, l, t, f, img);
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

void	events2(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f, t_image *img)
{
  int	next;
  SDL_Event event;

  next = 1;
  refresh(w, l, t, f, img);
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  clean_exit(w, m, l, t);
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    pars_scene(w, m, l, t, f);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_RETURN:
	      pars_scene(w, m, l, t, f);
	      break;
	    case SDLK_SPACE:
	      pars_scene(w, m, l, t, f);
	      break;
	    case SDLK_LEFT:
	      history_navigation(w, m, l, t, f, img);
	      break;
	    case SDLK_m:
	      music_pause(m);
	      break;
	    case SDLK_ESCAPE:
	      game_menu(w, m, l, t, f, img);
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

void	events(t_window *w, t_music *m, t_list *l, t_text *t, t_font *f)
{
  int	next;
  SDL_Event event;

  next = 1;
  while (next)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  next = 0;
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    pars_scene(w, m, l, t, f);
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      next = 0;
	      break;
	    case SDLK_RETURN:
	      pars_scene(w, m, l, t, f);
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
