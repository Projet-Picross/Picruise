//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#define N 10

void pause();

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
        SDL_Window* window;
        SDL_Renderer* renderer;

        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
                return 1;

        // Create the window where we will draw.
        window = SDL_CreateWindow("PICROSS",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        SCREEN_WIDTH, SCREEN_HEIGHT,
                        0);

        // We must call SDL_CreateRenderer in order for draw calls to affect this window.
        renderer = SDL_CreateRenderer(window, -1, 0);

        // Select the color for drawing. It is set to red here.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

        // Give us time to see the window.
        //SDL_Delay(5000);
				pause();

        // Always be sure to clean up
        SDL_Quit();
        return 0;
}

void pause()
{
	int continuer = 1;
	SDL_Event event;

	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				continuer = 0;
		}
	}
}
