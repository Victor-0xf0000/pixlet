#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

typedef struct window Window;

typedef struct renderer
{
  void* pixels;
  SDL_Renderer* sdl_renderer_ptr;
  SDL_Surface* sprite_surface;
  int cr, cg, cb; // clear colors
  int sw, sh, pw, ph;
} Renderer;

Renderer* create_renderer(Window* window, int sprite_w, int sprite_h, int pixel_w, int pixel_h);
void destroy_renderer(Renderer* renderer);

void renderer_setSpriteClearColor(Renderer* renderer, int r, int g, int b);
void renderer_setSpritePixel(Renderer* renderer, int x, int y, int r, int g, int b, int a);

void renderer_saveToFile(Renderer* renderer, const char* path);
void renderer_loadFromFile(Renderer* renderer, const char* path);

void renderer_begin(Renderer* renderer);
void render_sprite(Renderer* renderer);
void renderer_end(Renderer* renderer);

#endif // RENDERER_H
