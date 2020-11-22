#include <SDL2/SDL.h>
#include <vector>

#include "Envelope.h"
#include "Waveforms.h"

#include "Synthesizer.h"

using namespace VSynth;

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    Synthesizer synth;
    synth.open();
    synth.unpause();

    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
    }
    
    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}