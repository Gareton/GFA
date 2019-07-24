#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

GLuint shd::Shader::_USE_ID = 0;


shd::Shader::Shader(dtli::DataLoaderInterface *loader, const std::string &vShaderPath, const std::string &fShaderPath, const std::string &gShaderPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::string geometrySource;

	try {
		vertexSource = std::move(loader->loadFile(vShaderPath));
		fragmentSource = std::move(loader->loadFile(fShaderPath));
		geometrySource = std::move(loader->loadFile(gShaderPath));
	}

	catch (dtli::LoadingFailure &f)
	{
		throw shd::ShaderCreatingFailed("FAILED TO LOAD SOURCE FILE:" + f.getPath());
	}

	compile(vertexSource, fragmentSource, geometrySource);
}

shd::Shader::Shader(dtli::DataLoaderInterface *loader, const std::string &vShaderPath, const std::string &fShaderPath)
{
	std::string vertexSource;
	std::string fragmentSource;

	try {
		vertexSource = loader->loadFile(vShaderPath);
		fragmentSource = loader->loadFile(fShaderPath);
	}

	catch (dtli::LoadingFailure &f)
	{
		throw shd::ShaderCreatingFailed("FAILED TO LOAD SOURCE FILE:" + f.getPath());
	}

	compile(vertexSource, fragmentSource);
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

GLuint shd::Shader::GetID()
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

void shd::Shader::compile(const std::string &vSource, const std::string &fSource, const std::string &gSource)
{
	GLuint vShader, fShader, gShader;

	vShader = createShader(obj_type::vertexShader, vSource);
	fShader = createShader(obj_type::fragmentShader, fSource);
	gShader = createShader(obj_type::geometryShader, gSource);

	_id = glCreateProgram();

	glAttachShader(_id, vShader);
	glAttachShader(_id, fShader);
	glAttachShader(_id, gShader);

	glLinkProgram(_id);
	checkErrors(_id, obj_type::shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteShader(gShader);
}

void shd::Shader::compile(const std::string &vSource, const std::string &fSource)
{
	GLuint vShader, fShader;

	vShader = createShader(obj_type::vertexShader, vSource);
	fShader = createShader(obj_type::fragmentShader, fSource);

	_id = glCreateProgram();

	glAttachShader(_id, vShader);
	glAttachShader(_id, fShader);

	glLinkProgram(_id);
	checkErrors(_id, obj_type::shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

GLuint shd::Shader::createShader(obj_type type, const std::string &source)
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

	const char *c_str = source.c_str();

	glShaderSource(shader, 1, &c_str, nullptr);
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

