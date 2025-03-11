#include <bitset>
#include <vector>

const unsigned int MAX_ENTITIES = 32;

typedef std::bitset<MAX_ENTITIES> Signature;

struct IComponent {
	protected:
		static int nextId;
};

template <typename T> 
class Component: public IComponent {
	static int GetId() {
		static auto id = nextId++;
		return id;
	}

};

class Entity {
	private:
		int id;

	public:
		Entity(int id) : id(id) {}
		int GetId() const;

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

		template <typename TComponent> void RequireComponent();

};

class Registry {
};

template  <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componetentSignature.set(componentId);
}