//------------------------------------------------------------
// <copyright file="Resources.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_RESOURCES_HPP
#define TEASER_RESOURCES_HPP

#include <Teaser/Common.hpp>
#include <Teaser/ResourceHolder.hpp>
#include <Teaser/Texture.hpp>
#include <Teaser/ShaderProgram.hpp>

namespace Teaser
{

using ShaderHolder = ResourceHolder<ShaderProgram, std::string>;
using TextureHolder = ResourceHolder<Texture, std::string>;

extern ShaderHolder g_shaders;
extern TextureHolder g_textures;

} // namespace Teaser

#endif // TEASER_RESOURCES_HPP