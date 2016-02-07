//------------------------------------------------------------
// <copyright file="Component.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------


#ifndef TEASER_COMPONENT_HPP
#define TEASER_COMPONENT_HPP

#include <cstddef>
#include <bitset>
#include <array>
#include <type_traits>

#include <Teaser/Common.hpp>

namespace Teaser
{
	class GameObject;

	using ComponentID = std::size_t;

	namespace Internal
	{
		inline ComponentID generateNextComponentId() noexcept
		{
			static ComponentID lastID{ 0u };
			return lastID++;
		}
	}

	template<typename T>
	inline ComponentID getComponentID() noexcept
	{
		static_assert(std::is_base_of<Component, T>::value,
			"Type must inherit from Component to get it's ID");
		static ComponentID id = Internal::generateNextComponentId();
		return id;
	}


	constexpr std::size_t maxComponents{ 64 };

	class Component
	{
	public:

		Component() {}

		virtual ~Component() {}

		virtual void start() {}
		virtual void update(float dt) {}
		virtual void draw(float dt) {}

		GameObject *gameObject{ nullptr };
	};

	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;


} // namespace Teaser

#endif //TEASER_COMPONENT_HPP
