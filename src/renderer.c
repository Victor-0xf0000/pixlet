#include <renderer.h>
#include <window.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

Renderer* create_renderer(Window* window, int sprite_w, int sprite_h, int pixel_w, int pixel_h)
{
  Renderer* renderer = (Renderer*) malloc(sizeof(Renderer));
  renderer->pixels = (void*) malloc(sizeof(Uint32)*sprite_w*sprite_h);
  memset(renderer->pixels, 0, sprite_w*sprite_h);
  renderer->sdl_renderer_ptr = SDL_CreateRenderer(window->sdl_window_ptr, 
      -1, 
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  renderer->sprite_surface = SDL_CreateRGBSurface(0, 
      sprite_w, sprite_h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
  renderer->cr = 0;  
  renderer->cg = 0;  
  renderer->cb = 0;
  renderer->pw = pixel_w;
  renderer->ph = pixel_h;
  renderer->sw = sprite_w;
  renderer->sh = sprite_h;
  return renderer;
}

void destroy_renderer(Renderer* renderer)
{
  SDL_DestroyRenderer(renderer->sdl_renderer_ptr);
  SDL_FreeSurface(renderer->sprite_surface);
  free(renderer->pixels);
}

void renderer_setSpriteClearColor(Renderer* renderer, int r, int g, int b)
{
  renderer->cr = r;
  renderer->cg = g;
  renderer->cb = b;
}

void renderer_setSpritePixel(Renderer* renderer, int x, int y, int r, int g, int b, int a)
{
  Uint32* const target_pixel = (Uint32*) ((Uint8*) renderer->sprite_surface->pixels
                                          + y * renderer->sprite_surface->pitch
                                          + x * renderer->sprite_surface->format->BytesPerPixel);
  *target_pixel = SDL_MapRGBA(renderer->sprite_surface->format, r, g, b, a);
}

void renderer_saveToFile(Renderer* renderer, const char* path)
{
  IMG_SavePNG(renderer->sprite_surface, path);  
}

void renderer_loadFromFile(Renderer* renderer, const char* path)
{
  renderer->sprite_surface = IMG_Load(path);
}

void renderer_begin(Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer->sdl_renderer_ptr, 30, 30, 30, 255);
  SDL_RenderClear(renderer->sdl_renderer_ptr);
  SDL_Rect background = {0, 0, renderer->sw*renderer->pw, renderer->sh*renderer->ph};
  SDL_SetRenderDrawColor(renderer->sdl_renderer_ptr, 50, 50, 50, 255);
  SDL_RenderFillRect(renderer->sdl_renderer_ptr, &background);
}

void render_sprite(Renderer* renderer)
{
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->sdl_renderer_ptr, renderer->sprite_surface);
  SDL_Rect dst = {0, 0, renderer->sw*renderer->pw, renderer->sh*renderer->ph};
  SDL_RenderCopy(renderer->sdl_renderer_ptr, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void renderer_end(Renderer* renderer)
{
  SDL_RenderPresent(renderer->sdl_renderer_ptr);
}
