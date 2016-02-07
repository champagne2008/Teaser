#include "GOManager.hpp"

namespace Teaser
{
	GOManager::GOManager() 
	{
		for (unsigned int id = 1; id <= MAXGAMEOBJECTS; id++) 
		{
			availableIds.push(id);
		}
	}

	void GOManager::insertOldID(GameObjectID id)
	{
		availableIds.push(id);
	}

	GameObjectID Teaser::GOManager::generateNextGOID()
	{
		GameObjectID id = availableIds.top();
		availableIds.pop();
		return id;
	}

} // namespace Teaser
