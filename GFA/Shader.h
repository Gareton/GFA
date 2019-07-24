#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "DataLoaderInterface.h"

namespace shd {

	enum obj_type { vertexShader, fragmentShader, geometryShader, shaderProgram };

	class ShaderCreatingFailed {
	public:
		ShaderCreatingFailed(const std::string &message) { _message = message; }
		std::string what() { return _message; }
	private:
		std::string _message;
	};

	class Shader {
	public:
		Shader(dtli::DataLoaderInterface *loader, const std::string &vShaderPath, const std::string &fShaderPath, const std::string &gShaderPath);
		Shader(dtli::DataLoaderInterface *loader, const std::string &vShaderPath, const std::string &fShaderPath);
		~Shader();
		GLuint GetID();
		void setUniform(const std::string &name, const int &value);
		void setUniform(const std::string &name, const float &value);
		void setUniformVec4(const std::string &name, const glm::vec4 &vec);
		void setUniformVec3(const std::string &name, const glm::vec3 &vec);
		void setUniformVec2(const std::string &name, const glm::vec2 &vec);
		void setUniformMat4(const std::string &name, const glm::mat4 &mat);
		void setUniformMat3(const std::string &name, const glm::mat3 &mat);
	private:
		Shader(Shader &s);
		Shader &operator=(Shader &s) {}
		void compile(const std::string &vSource, const std::string &fSource, const std::string &gSource);
		void compile(const std::string &vSource, const std::string &fSource);
		void checkErrors(GLuint objectID, obj_type type);
		GLuint createShader(obj_type type, const std::string &source);

		GLuint _id;
		static GLuint _USE_ID; //id of a current using shader
	};

}