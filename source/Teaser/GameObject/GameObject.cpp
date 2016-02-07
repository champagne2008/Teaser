//------------------------------------------------------------
// <copyright file="GameObject.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/GameObject/GameObject.hpp>

namespace Teaser
{

	GameObject::GameObject() 
		: transform(addComponent<Transform>())
	{};

	GameObject::~GameObject() {};

	void GameObject::destroy() 
	{ 
		m_bAlive = false; 
	}

	void GameObject::update(float dt)
	{
		for (auto& c : components)
			c->update(dt);
	}

	void GameObject::draw(float dt)
	{
		for (auto& c : components)
			c->draw(dt);
	}

} // namespace Teaser

