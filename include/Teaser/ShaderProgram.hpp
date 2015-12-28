//------------------------------------------------------------
// <copyright file="ShaderProgram.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_SHADER_HPP
#define TEASER_SHADER_HPP

#include <Teaser/Common.hpp>
#include <string>

namespace Teaser
{

enum ShaderType : GLenum
{
	VertexShader = GL_VERTEX_SHADER,
	FragmentShader = GL_FRAGMENT_SHADER
};

class ShaderProgram
{

public:
	

	ShaderProgram()
	: m_linked(false)
	, m_isValid(false)
	, m_handle(0){};

	~ShaderProgram(){};

	void create();

	bool addShader(ShaderType type, std::string source);
	bool addShaderFromFile(ShaderType type, std::string path);

	bool link();

	inline bool isLinked() const { return m_linked; }

	inline bool isValid() const { return m_isValid; }

	inline void use() { glUseProgram(m_handle); }
	inline void unUse() { glUseProgram(0); }

	inline std::string getError() const { return m_error; }

	i32 getUniformLocation(std::string name);

	inline void setUniform(std::string name, u32 x)
	{
		glUniform1ui(getUniformLocation(name), x);
	}

	inline void setUniform(std::string name, f32 x)
	{
		glUniform1f(getUniformLocation(name), x);
	}
	inline void setUniform(std::string name, f32 x, f32 y)
	{
		glUniform2f(getUniformLocation(name), x, y);
	}
	inline void setUniform(std::string name, f32 x, f32 y, f32 z)
	{
		glUniform3f(getUniformLocation(name), x, y, z);
	}

private:
	std::string m_error;
	bool m_isValid;
	bool m_linked;
	u32 m_handle;
};

} // namespace Teaser

#endif // TEASER_SHADER_HPP