//------------------------------------------------------------
// <copyright file="Common.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------



#ifndef TEASER_COMMON_HPP
#define TEASER_COMMON_HPP

#include <Teaser/OpenGL.hpp>
#include <Teaser/Types.hpp>
#include <Teaser/Math/Constants.hpp>

#include <assert.h>
#include <iostream>
// TODO(Markus): create own assertion method
#define tassert(x, msg) assert(x&& msg)

#ifndef NDEBUG 
#define TEASER_DEBUG 
#endif //NDEBUG

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