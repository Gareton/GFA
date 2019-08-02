#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

GLuint shd::Shader::_USE_ID = 0;


shd::Shader::Shader(TextFile vShaderFile, TextFile fShaderFile, TextFile gShaderFile)
{
	compile(vShaderFile.getText(), fShaderFile.getText(), gShaderFile.getText());
}

shd::Shader::Shader(TextFile vShaderFile, TextFile fShaderFile)
{
	compile(vShaderFile.getText(), fShaderFile.getText());
}

shd::Shader::~Shader()
{
	if (_USE_ID == _id)
	{
		glUseProgram(0);
		_USE_ID = 0;
	}

	glDeleteProgram(_id);
}

GLuint shd::Shader::getID()
{
	return _id;
}

void shd::Shader::setUniform(const std::string &name, const int &value)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void shd::Shader::setUniform(const std::string &name, const float &value)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void shd::Shader::setUniformVec4(const std::string &name, const glm::vec4 &vec)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniform4f(glGetUniformLocation(_id, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void shd::Shader::setUniformVec3(const std::string &name, const glm::vec3 &vec)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniform3f(glGetUniformLocation(_id, name.c_str()), vec.x, vec.y, vec.z);
}

void shd::Shader::setUniformVec2(const std::string &name, const glm::vec2 &vec)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniform2f(glGetUniformLocation(_id, name.c_str()), vec.x, vec.y);
}

void shd::Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void shd::Shader::setUniformMat3(const std::string &name, const glm::mat3 &mat)
{
	if (_USE_ID != _id)
	{
		glUseProgram(_id);
		_USE_ID = _id;
	}

	glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void shd::Shader::compile(const char *vSource, const char *fSource, const char *gSource)
{
	GLuint vShader, fShader, gShader;

	vShader = createShader(obj_type::vertexShader, vSource);
	fShader = createShader(obj_type::fragmentShader, fSource);

	if(gSource != nullptr)
		gShader = createShader(obj_type::geometryShader, gSource);

	_id = glCreateProgram();

	glAttachShader(_id, vShader);
	glAttachShader(_id, fShader);

	if (gSource != nullptr)
		glAttachShader(_id, gShader);

	glLinkProgram(_id);
	checkErrors(_id, obj_type::shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	if (gSource != nullptr)
		glDeleteShader(gShader);
}

GLuint shd::Shader::createShader(obj_type type, const char *source)
{
	GLuint shader = 0;


	switch (type)
	{
	case obj_type::vertexShader:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;

	case obj_type::fragmentShader:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	case obj_type::geometryShader:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	checkErrors(shader, type);

	return shader;
}

void shd::Shader::checkErrors(GLuint objectID, obj_type type)
{
	GLint success;
	static GLchar infoLog[1024];

	for (GLchar &byte : infoLog)
		byte = static_cast<char>(0);

	if (type != obj_type::shaderProgram)
	{
		glGetShaderiv(objectID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(objectID, 1024, NULL, infoLog);
			throw(ShaderCreatingFailed(infoLog));
		}
	}
	else
	{
		glGetProgramiv(objectID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(objectID, 1024, NULL, infoLog);
			throw(ShaderCreatingFailed(infoLog));
		}
	}
}

