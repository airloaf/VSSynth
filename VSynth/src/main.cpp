#include <SDL2/SDL.h>

int main(int argc, char *argv[]){

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    int x = 2;

    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
    }
    x = 0;

    SDL_DestroyWindow(window);

    return 0;
}