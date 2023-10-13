#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct rect {
    float x;
    float y;
    float w;
    float h;
} rect;

int xdir = 1;
int ydir = 1;

int init_window(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "error init sdl\n");
        return FALSE;
    }
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
            );
    if (!window){
        fprintf(stderr, "error creating window\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        fprintf(stderr, "error renderer\n");
        return FALSE;
    }
    return TRUE;
}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            if (event.key.keysym.sym == SDLK_UP){
                ydir = -1;
                //rect.y-=2;
            }
            if (event.key.keysym.sym == SDLK_DOWN){
                ydir = 1;
                //rect.y+=2;
            }
            if (event.key.keysym.sym == SDLK_LEFT){
                xdir = -1;
                //rect.x-=2;
            }
            if (event.key.keysym.sym == SDLK_RIGHT){
                xdir = 1;
                //rect.x+=2;
            }
            break;
    }
}

void setup(){
    rect.x = 20;
    rect.y = 20;
    rect.w = 15;
    rect.h = 15;
}

void update(){
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();


    rect.x+=50 * xdir * delta_time;
    rect.y+=70 * ydir * delta_time;
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect1 = {
        (int)rect.x,
        (int)rect.y,
        (int)rect.w,
        (int)rect.h,
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);

    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(){
    game_is_running = init_window();
    
    setup();
    while (game_is_running){
        process_input();
        update();
        render();
    }

    return 0;
}
