//------------------------------------------------------------
// <copyright file="ShaderProgram.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/ShaderProgram.hpp>

#include <fstream>
#include <vector>

using namespace Teaser;

unsigned int ShaderProgram::getUniformLocation(std::string name)
{
	return glGetUniformLocation(m_handle, name.c_str());
}

void ShaderProgram::create() { m_handle = glCreateProgram(); }

ShaderProgram* ShaderProgram::loadShaderFromFile(std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
	ShaderProgram* shader = new ShaderProgram();

	shader->create();

	shader->addShaderFromFile(ShaderType::VertexShader, vertexShader);
	shader->addShaderFromFile(ShaderType::FragmentShader, fragmentShader);

	//TODO(markus): implement geometryShader
	//if(!geometryShader.empty())
	//shader->addShaderFromFile(ShaderType::GeometryShader, geometryShader);

	shader->link();
	return shader;
}

bool ShaderProgram::addShaderFromFile(ShaderType type, std::string path)
{
	std::ifstream myfile(path);
	std::string source;
	if (myfile.is_open())
	{
		std::string line;
		while (std::getline(myfile, line))
		{
			source += line + "\n";
		}
		myfile.close();
	}
	else
	{
		fatal("Failed to open File at: " + path);
		return false;
	}

	return addShader(type, source);
}

bool ShaderProgram::addShader(ShaderType type, std::string source)
{

	if (!m_handle)
	{
		fatal("ShaderProgram::create() must be called before adding Shader!");
		return false;
	}
	unsigned int shader = glCreateShader(type);

	const GLchar* s = source.c_str();
	glShaderSource(shader, 1, &s, NULL);
	glCompileShader(shader);

	int isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shader); // Don't leak the shader.
		m_error = &errorLog[0];
		fatal(m_error);
		return false;
	}
	glAttachShader(m_handle, shader);

	return true;
}

bool ShaderProgram::link()
{

	glLinkProgram(m_handle);

	int isLinked = 0;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_handle, maxLength, &maxLength, &errorLog[0]);

		m_error = &errorLog[0];
		fatal(m_error);
		return false;
	}

	m_isValid = (isLinked != GL_FALSE);
	return true;
}
