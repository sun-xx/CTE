#include <SDL2/SDL.h> /*All SDL App's need this*/
#include <stdio.h>
int main(int argc,char *argv[])
{
	printf("Initializing SDL."); /* Initialize defaults, Video and Audio */
	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1))
	{
		printf("Could not initialize SDL: %s.", SDL_GetError());
		exit(-1);
	}
	printf("SDL initialized.");
	printf("Quiting SDL."); /* Shutdown all subsystems */
	SDL_Quit();
	printf("Quiting....");
	exit(0);
}
