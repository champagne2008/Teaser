//------------------------------------------------------------
// <copyright file="GameObject.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_GAMEOBJECT_HPP
#define TEASER_GAMEOBJECT_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Transform.hpp>
#include <Teaser/GameObject/Component.hpp>

#include <memory>
#include <vector>


namespace Teaser
{

using GameObjectID = unsigned int;

class GameObject
{
public:

	~GameObject();

	friend class GOManager;

	inline GameObjectID getID() { return id; }

	inline bool isAlive() { return m_bAlive; }

	void destroy();

	ComponentBitset componentBitset;
	ComponentArray componentArray;

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		tassert(!hasComponent<T>(), std::string("Duplication of component:\n\n " + getTypeName<T>()) );
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->gameObject = this;

		std::unique_ptr<Component> uPtr{c};
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentID<T>()] = c;
		componentBitset[getComponentID<T>()] = true;

		c->start();
		return *c;
	}

	template<typename T>
	T& getComponent() const
	{
		tassert(hasComponent<T>(),"Component not found at Gameobject");
		auto ptr(componentArray[getComponentID<T>()]);
		return *reinterpret_cast<T*>(ptr);
	}

	template<typename T>
	bool makeSureHasComponent() 
	{
		if (!hasComponent<T>()) 
		{
			addComponent<T>();
			return true
		}
		return bool;
	}

	template<typename T>
	bool hasComponent() const
	{
		return componentBitset[getComponentID<T>()];
	}

	Transform& transform;

private:

	GameObject();

	void update(float dt);

	void draw(float dt);

	GameObjectID id;

	bool m_bAlive = true;
	std::vector<std::unique_ptr<Component>> components;

	
};

} // namespace Teaser

#endif // TEASER_GAMEOBJECT_HPP
