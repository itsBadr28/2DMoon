#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <fstream>

#include "Game.h"

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../System/MovementSystem.h"
#include "../System/RenderSystem.h"
#include "../System/AnimationSystem.h"
#include "../System/CollisionSystem.h"
#include "../System/RenderColliderSystem.h"
#include "../System/DamageSystem.h"

#include "../ECS/ECS.h"
#include "../Logger/Logger.h"

Game::Game() {
	isRunning = false;
	isDebug = false;
	registry = std::make_unique<Registry>();
	assetStore = std::make_unique<AssetStore>();
	//eventBus = std::make_unique<EventBus>();
	Logger::Log("Game connstructor called!");
}

Game::~Game() {
	Logger::Log("Game destructor called!");
}

void Game::LoadLevel(int level) {

	// add systems
	registry->AddSystem<MovementSystem>();
	registry->AddSystem<RenderSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<CollisionSystem>();
	registry->AddSystem<RenderColliderSystem>();
	//registry->AddSystem<DamageSystem>();


	assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
	assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");
	assetStore->AddTexture(renderer, "chopper-image", "./assets/images/chopper.png");
	assetStore->AddTexture(renderer, "player-idel-image", "./assets/images/_Idle.png");
	assetStore->AddTexture(renderer, "player-roll-image", "./assets/images/_Roll.png");
	assetStore->AddTexture(renderer, "tileset-image", "./assets/tilemaps/jungle.png");



	// load tilemap 
	int tileSize = 32;
	double tileScale = 2.0;
	int mapNumCols = 25;
	int mapNumRows = 20;

	std::fstream mapFile;
	mapFile.open("./assets/tilemaps/jungle.map");
	for (int y = 0; y < mapNumRows; y++) {
		for (int x = 0; x < mapNumCols; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = atoi(&ch) * tileSize;
			mapFile.ignore();

			Entity tile = registry->CreateEntity();
			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileSize * tileScale), y * (tileSize * tileScale)), glm::vec2(tileScale, tileScale), 0.0);
			tile.AddComponent<SpriteComponent>("tileset-image", tileSize, tileSize, 0, srcRectX, srcRectY);
		}
	}
	mapFile.close();

	Entity player = registry->CreateEntity();
	player.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
	player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	player.AddComponent<SpriteComponent>("player-idel-image", 120, 80, 1);
	player.AddComponent<AnimationComponent>(10, 5, true);
	player.AddComponent<BoxColliderComponent>(24, 32, glm::vec2(24 + 24/2, 32 + 32/2));

	Entity player1 = registry->CreateEntity();
	player1.AddComponent<TransformComponent>(glm::vec2(200.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
	player1.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));
	player1.AddComponent<SpriteComponent>("player-roll-image", 120, 80, 1);
	player1.AddComponent<AnimationComponent>(12, 12, true);
	player1.AddComponent<BoxColliderComponent>(24, 32, glm::vec2(24 + 24 / 2, 32 + 32 / 2));


	Entity chopper = registry->CreateEntity();
	chopper.AddComponent<TransformComponent>(glm::vec2(10.0, 20.0), glm::vec2(3.0, 3.0), 0.0);
	chopper.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 2);
	chopper.AddComponent<AnimationComponent>(2, 10, true);
	 
	Entity tank = registry->CreateEntity();
	tank.AddComponent<TransformComponent>(glm::vec2(500.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
	tank.AddComponent<RigidBodyComponent>(glm::vec2(-30.0, 0.0));
	tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 2);
	tank.AddComponent<BoxColliderComponent>(32, 32);

	Entity truck = registry->CreateEntity();
	truck.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
	truck.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 3);
	truck.AddComponent<BoxColliderComponent>(32, 32);



}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		Logger::Err("Error initializing SDL.");
		return;
	}
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = displayMode.w;
	windowHeight = displayMode.h;
	window = SDL_CreateWindow(
		"2D Moon",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		0
	);

	if (!window) {
		Logger::Err("Error creating SDL window.");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		Logger::Err("Error creating SDL renderer.");
		return;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	isRunning = true;
}

void Game::Setup() {
	LoadLevel(1);
}
void Game::Run() {
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() { 
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		switch (sdlevent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlevent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
				return;
			}
			if (sdlevent.key.keysym.sym == SDLK_CAPSLOCK) {
				isDebug = !isDebug;
			}
			break;
		}
	}
}

void Game::Update() {

	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0f;

	 millisecondsPreviousFrame = SDL_GetTicks();


	 //eventBus->Reset();
	 // subscribes of events
	 //registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);

	 registry->Update();

     registry->GetSystem<MovementSystem>().Update(deltaTime);
	 registry->GetSystem<AnimationSystem>().Update();
	 registry->GetSystem<CollisionSystem>().Update(eventBus);


}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	registry->GetSystem<RenderSystem>().Update(renderer, assetStore);
	if (isDebug) {
		registry->GetSystem<RenderColliderSystem>().Update(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
