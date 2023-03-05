#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct window
{
  SDL_Window* sdl_window_ptr;
} Window;

Window* create_window(const char* title, int width, int height);
void destroy_window(Window* window);

#endif
