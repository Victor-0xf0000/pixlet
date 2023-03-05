#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdlib.h>

#include <window.h>
#include <renderer.h>

typedef struct pixel
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Pixel;

#define WIDTH   64 
#define HEIGHT  64
#define PIXEL_W 8
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
SDL_Surface* load_surface(const char* file_name)
{
  return IMG_Load(file_name);
}
int main(int argc, const char** argv)
{
  printf("Welcome to pixlet!\n");

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  Window* window = create_window("pixlet!", 800, 600);
  Renderer* renderer = create_renderer(window, WIDTH, HEIGHT, PIXEL_W, PIXEL_H);
  int should_quit = 0;
  SDL_SetRenderDrawBlendMode(renderer->sdl_renderer_ptr, SDL_BLENDMODE_BLEND);
  
  if (argc > 1)
  {
    printf("path: %s\n", argv[1]);
    renderer_loadFromFile(renderer, argv[1]);
  }

  int button = -1;
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
              button = SDL_BUTTON_RIGHT;
            if (e.button.button == SDL_BUTTON_LEFT)
              button = SDL_BUTTON_LEFT;
            break;
          }
        case SDL_MOUSEBUTTONUP:
          {
            button = -1;
            
            break;
          }
          
      }
    }
    
    renderer_begin(renderer);
    
    if (mx > 0 && mx < WIDTH*PIXEL_W && my > 0 && my < HEIGHT*PIXEL_H)
    {
      int x = (int) mx / PIXEL_W;
      int y = (int) my / PIXEL_H;
      int i = x + y * WIDTH;

      if (button == SDL_BUTTON_RIGHT)
      {
        renderer_setSpritePixel(renderer, x, y, 0, 0, 0, 0);
      }
      if (button == SDL_BUTTON_LEFT)
      {
        renderer_setSpritePixel(renderer, x, y, 200, 200, 200, 100);
      }
    }
    
    render_sprite(renderer);
     
    renderer_end(renderer);
  }
  
  renderer_saveToFile(renderer, 
      "C:\\Users\\isaias\\Documents\\victor\\pixlet\\build\\ab.png");

  destroy_window(window);
  destroy_renderer(renderer);
  return 0;
}
