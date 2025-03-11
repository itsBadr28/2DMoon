/*#ifndef GAME.H
#define GAME.H*/
#include <SDL.h>

const int FPS = 144;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
	private:
		bool isRunning;
		int millisecondsPreviousFrame = 0;
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:
		Game();
		~Game();
		void Initialize();
		void Run();
		void ProcessInput();
		void Update();
		void Setup();
		void Render();
		void Destroy();
		int windowWidth;
		int windowHeight;
};

//#endif
