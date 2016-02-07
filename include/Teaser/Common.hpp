//------------------------------------------------------------
// <copyright file="Common.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------



#ifndef TEASER_COMMON_HPP
#define TEASER_COMMON_HPP

#ifndef TEASER_STDPRECISION
#define TEASER_STDPRECISION double
#endif

#include <Teaser/OpenGL.hpp>
#include <Teaser/Types.hpp>
#include <Teaser/Math/Constants.hpp>

#define STRFY(x) _STRFY(x)

#define _STRFY(x) #x

#include <assert.h>
#include <iostream>
#include <typeinfo>
// TODO(Markus): create own assertion method
#define tassert(x, msg) if(!(x)){fatal(msg);}

#ifndef NDEBUG 
#define TEASER_DEBUG 
#endif //NDEBUG


//Try to avoid this as often as possible
template<typename T>
std::string getTypeName() 
{
	//Check which compiler we are using
#ifdef _MSC_VER 
	std::string name = typeid(T).name();
	//name.erase(0, 6);
#else
	std::string name = "[getTypeName() not implemented on this compiler]";
#endif
	//visual studio implements it as: class namespace::classname
	return name;
}

namespace Teaser
{
enum class MessageBoxType
{
	Information,
	Warning,
	Error
};

void showMessageBox(MessageBoxType type, std::string title, std::string msg);
void fatal(std::string msg);

} // namespace Teaser

#endif // TEASER_COMMON_HPP