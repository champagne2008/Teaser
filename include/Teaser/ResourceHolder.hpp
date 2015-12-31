//------------------------------------------------------------
// <copyright file="ResourceHolder.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_RESOURCEHOLDER_HPP
#define TEASER_RESOURCEHOLDER_HPP

#include <map>
#include <Teaser/Common.hpp>

namespace Teaser
{

template <typename ResourceType, typename KeyType>
class ResourceHolder
{
public:
	ResourceHolder() = default;
	~ResourceHolder() { clearAll(); }

	bool erase(KeyType key)
	{
		auto it = m_resources.find(key);
		if (it != m_resources.end())
		{
			delete it.second;
			m_resources.erase(it);
			return true;
		}
		return false;
	}

	bool hasItem(KeyType key)
	{
		auto it = m_resources.find(key);
		return (it != m_resources.end());
	}

	void clearAll()
	{
		auto it = m_resources.begin();
		for (; it != m_resources.end(); ++it)
		{
			delete it->second;
		}
		m_resources.clear();
	}

	void insert(ResourceType* res, KeyType key)
	{
		m_resources.insert(std::make_pair(key, res));
	}

	ResourceType& get(KeyType key) const
	{
		auto it = m_resources.find(key);
		if (it != m_resources.end())
		{
			return *it->second;
		}

		fatal("Failed to find resource with key : " + key);

		return ResourceType();
	}

	ResourceType& operator[](KeyType key) const { return get(key); }

private:
	std::map<KeyType, ResourceType*> m_resources;
};

} // namespace Teaser

#endif // TEASER_RESOURCEHOLDER_HPP