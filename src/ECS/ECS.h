#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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
		Entity(const Entity& entity) = default;
		int GetId() const;


		Entity& operator = (const Entity& other) = default;
		bool operator == (const Entity& other) const { return id == other.id; }

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

class IPool {
	public:
		virtual ~IPool() {}
};

template <typename T>
class Pool: IPool {
	private: 
		std::vector<T> data;
	public:
		Pool(int size = 100) {
			data.reserve(size);
		}
		virtual ~Pool() = default;

		bool isEmpty() const {
			return data.empty();
		}

		int GetSize() const {
			return data.size();
		}

		void Resize(int size) {
			data.reserve(size);
		}

		void Clear() {
			data.clear();
		}

		void Add(T element) {
			data.push_back(element);
		}

		void Set(int index, T object) {
			data[index] = object;
		}

		T& Get(int index) {
			return static_cast<T&>data[index];
		}

		T& operator[](unsigned int index) {
			return data[index];
		}


};

class Registry {
	private:
		int numEntities = 0;

		std::vector<IPool*> componentPools;

		std::vector<Signature> entityComponentSignatures;

		std::unordered_map<std::type_index, System*> systems;

		std::set<Entity> entitiesToBeAdded;
		std::set<Entity> entitiesToBeKilled;
	public:		
		Registry() = default;

		void Update();

		Entity CreateEntity();

		void AddEntityToSystem(Entity entity);

};

template  <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componetentSignature.set(componentId);
}