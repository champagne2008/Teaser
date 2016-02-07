//------------------------------------------------------------
// <copyright file="GOManager.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_GOMANAGER_HPP
#define TEASER_GOMANAGER_HPP

#include "GameObject.hpp"
#include <algorithm>
#include <memory>
#include <queue>
#include <functional>

namespace Teaser
{

	constexpr unsigned int MAXGAMEOBJECTS = 1024;

class GOManager
{
public:

	GOManager();
	~GOManager() {}

	GameObject& createGameObject() 
	{
		GameObject* ptr =  new GameObject();
		ptr->id = generateNextGOID();
		gameObjects.emplace_back(ptr);
		return *ptr;
	}

	GameObject& getGameObjectByID(GameObjectID id) 
	{
		std::vector<std::unique_ptr<GameObject>>::iterator it = std::find_if(gameObjects.begin(), gameObjects.end(),
		[id](const std::unique_ptr<GameObject>& go) 
		{
				return (go->getID() == id); 
		}
		);

		if (it == gameObjects.end())
			fatal("No gameObject of id: " + std::to_string(id) + " could be found!");

		return *(it->get()); //Get the reference
	}

	void cleanUp() 
	{
		(gameObjects.erase(std::remove_if(std::begin(gameObjects),std::end(gameObjects),
			[this](const std::unique_ptr<GameObject>& go)
		{
			bool bRemove = !go->isAlive();
			if (bRemove)
				this->insertOldID(go->getID());
			return bRemove;
		}), std::end(gameObjects)));

	}
	void update(float dt) 
	{
		cleanUp();
		for (auto& go : gameObjects)go->update(dt);
	}

	void draw(float dt)
	{
		for (auto& go : gameObjects)go->draw(dt);
	}

	void insertOldID(GameObjectID id);
private:
	GameObjectID generateNextGOID();

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	//std::array<GameObject*, MAXGAMEOBJECTS> gameObjects;
	std::priority_queue<GameObjectID, std::vector<int>,std::greater<unsigned int>> availableIds;
};

} // namespace Teaser

#endif // TEASER_GOMANAGER_HPP