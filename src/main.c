#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct pixel
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Pixel;

#define WIDTH   32 
#define HEIGHT  32
#define PIXEL_W 16
#define PIXEL_H PIXEL_W   
 
#define WINDOW_WIDTH WIDTH * PIXEL_W + 200 
#define WINDOW_HEIGHT HEIGHT * PIXEL_H + 100 

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

void save_surface(const char* file_name, SDL_Renderer* renderer, SDL_Surface* surface) {
    IMG_SavePNG(surface, file_name);
}
int main(int argc, const char** argv)
{
  printf("Welcome to pixlet!\n");

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  SDL_Window* window = SDL_CreateWindow("pixlet", 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
      SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
  int should_quit = 0;
  
  SDL_Surface* screen_surface = SDL_GetWindowSurface(window);
  SDL_Surface* sprite_surface = SDL_CreateRGBSurface(0, 
      WIDTH, HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
  Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * WIDTH * HEIGHT);

  for (int i = 0; i < WIDTH * HEIGHT; i++)
  {
    pixels[i].r = 0;
    pixels[i].g = 0;
    pixels[i].b = 0;
    pixels[i].a = 0;
  }
  
  int button_right = 0;
  float framerate = 60.f;
  float st = 0.f;
  float dt = 0.f;
  while (!should_quit)
  {
    dt = SDL_GetTicks() - st;
    st = SDL_GetTicks();
    int mx, my;
    uint32_t state = SDL_GetMouseState(&mx, &my);
  
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
        case SDL_QUIT:
          should_quit = 1;
        case SDL_MOUSEBUTTONDOWN:
          {
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
              button_right = 1;
            }
            break;
          }
        case SDL_MOUSEBUTTONUP:
          {
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
              button_right = 0;
            }
            break;
          }
          
      }
    }
    
    SDL_SetRenderDrawColor(renderer, 29, 30, 30, 255);
    SDL_RenderClear(renderer);
    if (mx > 0 && mx < WIDTH*PIXEL_W && my > 0 && my < HEIGHT*PIXEL_H)
    {
      int x = (int) mx / PIXEL_W;
      int y = (int) my / PIXEL_H;
      int i = x + y * WIDTH;

      if (button_right)
      {
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
        pixels[i].a = 0;
        set_pixel(sprite_surface, x, y, SDL_MapRGBA(sprite_surface->format, 0, 0, 0, 0));
      }
      if ((state & SDL_BUTTON(1)) == SDL_PRESSED)
      {
        pixels[i].r = 40;
        pixels[i].g = 5;
        pixels[i].b = 100;
        pixels[i].a = 100;
        set_pixel(sprite_surface, x, y, SDL_MapRGBA(sprite_surface->format, 255, 255, 255, 255));
      }
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);  
    
    SDL_Rect dst = {0, 0, WIDTH*PIXEL_W, HEIGHT*PIXEL_H };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
  }
  
  save_surface("C:\\Users\\isaias\\Documents\\victor\\pixlet\\build\\test.png", 
      renderer, sprite_surface);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_FreeSurface(sprite_surface);
  free(pixels);
  return 0;
}
