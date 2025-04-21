#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.h>

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {
		for (auto& entity : GetSystemEntities()) {
			AnimationComponent& anmation = entity.GetComponent<AnimationComponent>();
			SpriteComponent& sprite = entity.GetComponent<SpriteComponent>();

			anmation.currentFrame = ((SDL_GetTicks() - anmation.startTime ) * anmation.frameSpeedRate / 1000 ) % anmation.numFrames;

			sprite.srcRect.x = sprite.width * anmation.currentFrame;

		}
	}
};

#endif // ANIMATIONSYSTEM_H