#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../Events/CollisionEvent.h"

#include "../EventBus/EventBus.h"

#include "../Logger/Logger.h"

class CollisionSystem : public System {
	public:
		CollisionSystem() {
			RequireComponent<TransformComponent>();
			RequireComponent<BoxColliderComponent>();
		}

	void Update(std::unique_ptr<EventBus>& eventBus) {
		auto entities = GetSystemEntities();
		
		for (auto i = entities.begin(); i != entities.end(); i++) {
			Entity& a = *i;
			auto& transformA = a.GetComponent<TransformComponent>();
			auto& colliderA = a.GetComponent<BoxColliderComponent>();

			for (auto j = i; j != entities.end(); j++) {
				Entity& b = *j;

				if (a == b) {
					continue;
				}

				auto& transformB = b.GetComponent<TransformComponent>();
				auto& colliderB = b.GetComponent<BoxColliderComponent>();

				bool collsioinHappened = CheckAABBCollision(
					transformA.position.x + colliderA.offset.x,
					transformA.position.y + colliderA.offset.y,
					colliderA.width,
					colliderA.height,
					transformB.position.x + colliderB.offset.x,
					transformB.position.y + colliderB.offset.y,
					colliderB.width,
					colliderB.height
				);

				if (collsioinHappened) {
					Logger::Log("Collision happened!");

					eventBus->EmitEvent<CollisionEvent>(a, b);
				}
			}
		}
	}

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {

		return (
			aX < bX + bW&&
			aX + aW > bX&&
			aY < bY + bH&&
			aY + aH > bY
			);
		
	}
};

#endif // COLLISIONSYSTEM_H