//------------------------------------------------------------
// <copyright file="ShaderProgram.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_SHADER_HPP
#define TEASER_SHADER_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math.hpp>

#include <string>
namespace Teaser
{

enum ShaderType : GLenum
{
	VertexShader   = GL_VERTEX_SHADER,
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

	static ShaderProgram* loadShaderFromFile(std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");

	void create();

	bool addShader(ShaderType type, std::string source);
	bool addShaderFromFile(ShaderType type, std::string path);

	bool link();

	inline bool isLinked() const { return m_linked; }

	inline bool isValid() const { return m_isValid; }

	inline ShaderProgram& use()
	{
		glUseProgram(m_handle);
		return *this;
	}
	inline void unUse() { glUseProgram(0); }

	inline std::string getError() const { return m_error; }

	unsigned int getUniformLocation(std::string name);

	inline ShaderProgram& setUniform(std::string name, int x)
	{
		glUniform1i(getUniformLocation(name), x);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, unsigned int x)
	{
		glUniform1ui(getUniformLocation(name), x);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, float x)
	{
		glUniform1f(getUniformLocation(name), x);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, float x, float y)
	{
		glUniform2f(getUniformLocation(name), x, y);
		return *this;
	}
	inline ShaderProgram& setUniform(std::string name, float x, float y, float z)
	{
		glUniform3f(getUniformLocation(name), x, y, z);
		return *this;
	}

	inline ShaderProgram&
	setUniform(std::string name, float x, float y, float z, float w)
	{
		glUniform4f(getUniformLocation(name), x, y, z, w);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, const Vector2& vec)
	{
		setUniform(name, vec.x, vec.y);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, const Vector3& vec)
	{
		setUniform(name, vec.x, vec.y, vec.z);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, const Vector4& vec)
	{
		setUniform(name, vec.x, vec.y, vec.z, vec.w);
		return *this;
	}

	inline ShaderProgram& setUniform(std::string name, const Matrix4& mat)
	{
		glUniformMatrix4fv(
		    getUniformLocation(name), 1, GL_FALSE, (const GLfloat*)mat.m);

		return *this;
	}

private:
	std::string m_error;
	bool m_isValid;
	bool m_linked;
	unsigned int m_handle;
};

} // namespace Teaser

#endif // TEASER_SHADER_HPP