#include <bitset>
#include <vector>

const unsigned int MAX_ENTITIES = 32;

typedef std::bitset<MAX_ENTITIES> Signature;

class Component {

};

class Entity {
	private:
		int id;

	public:
		Entity(int id) : id(id) {}
		int GetID() const;

};

class System {
	private: 
		Signature componetentSignature;
		std::vector<Entity> entities;

	public:
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		std::vector<Entity> GetSystenEntities() const;
		const Signature& GetComponentSignature() const;

};

class Registry {
};