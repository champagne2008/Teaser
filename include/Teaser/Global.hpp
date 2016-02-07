//------------------------------------------------------------
// <copyright file="Global.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_GLOBAL_HPP
#define TEASER_GLOBAL_HPP

namespace Teaser
{
template <typename T>
class Global
{
public:
	static void setSystem(T* system) 
	{ 
		if (sys != nullptr)
			delete sys;

		sys = system; 
	}

	static T*const getSystem() 
	{
		tassert((sys != nullptr), "Trying to access not setted System.");
		return sys; 
	}

	static void shutDown() { delete sys; }


	T* const operator ->() 
	{
		return Global<T>::getSystem();
	}
private:
	static T* sys;
};

template <typename T>
T* Global<T>::sys = nullptr;

} // namespace Teaser

#endif // TEASER_GLOBAL_HPP