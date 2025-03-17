#ifndef GAME_H  // Use underscore instead of period
#define GAME_H  // Use underscore instead of period
#include <SDL.h>
#include "../ECS/ECS.h"

const int FPS = 144;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
	private:
		bool isRunning;
		int millisecondsPreviousFrame = 0;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::unique_ptr<Registry> registry;

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


#endif // GAME_H 
