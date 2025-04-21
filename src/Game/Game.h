#ifndef GAME_H  // Use underscore instead of period
#define GAME_H  // Use underscore instead of period
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"

const int FPS = 144;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
	private:
		bool isRunning;
		bool isDebug;
		int millisecondsPreviousFrame = 0;
		SDL_Window* window;
		SDL_Renderer* renderer;

		std::unique_ptr<Registry> registry;
		std::unique_ptr<AssetStore> assetStore;
		std::unique_ptr<EventBus> eventBus;

	public:
		Game();
		~Game();
		void Initialize();
		void Run();
		void ProcessInput();
		void Update();
		void Setup();
		void LoadLevel(int level);
		void Render();
		void Destroy();
		int windowWidth;
		int windowHeight;
};


#endif // GAME_H 
