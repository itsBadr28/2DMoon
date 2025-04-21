#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"

#include "../Events/CollisionEvent.h"
#include "../EventBus/EventBus.h"

class DamageSystem : public System {
	public: 
		DamageSystem() {
			RequireComponent<BoxColliderComponent>();
		}

		void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
			eventBus->SubscribeToEvents<CollisionEvent>(this, &DamageSystem::onCollision);
		}

		void onCollision(CollisionEvent& event) {
			Logger::Log("Damage System received an event collision between entities: " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
			event.a.Kill();
			event.b.Kill();
		}

		void Update() {

		}

};

#endif // DAMAGESYSTEM_H