#include <window.h>
#include <stdlib.h>

Window* create_window(const char* title, int width, int height)
{
  Window* window = (Window*) malloc(sizeof(Window));
  window->sdl_window_ptr = SDL_CreateWindow(title, 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
      width, height, SDL_WINDOW_SHOWN);
  return window;  
}

void destroy_window(Window* window)
{
  SDL_DestroyWindow(window->sdl_window_ptr);
}
