#include "ECS.h"

int Entity::GetId() const {
	return id;
}


void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
	entities.erase(std::remove_if(std::begin(entities), std::end(entities), [&entity](const Entity& e) {
		return entity.GetId() == e.GetId();
	}), std::end(entities));
}

std::vector<Entity> System::GetSystenEntities() const {
	return entities;
}

const Signature& System::GetComponentSignature() const {
	return componetentSignature;
}