#include "shader.h"

#if(_ENGINE_RENDERER_OPENGL)

#include <string>
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../../io/utils/file_utils.h"


using namespace Engine::Core;

namespace Engine {  namespace Core {  namespace Graphics { namespace OpenGL {

	Shader::Shader(const char* vertPath, const char* fragPath)
		:m_VertPath(vertPath), m_FragPath(fragPath)
	{

		m_ShaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertPath = IO::FileUtils::read_file(m_VertPath);
		std::string fragPath = IO::FileUtils::read_file(m_FragPath);
		const char* vertSource = vertPath.c_str();
		const char* fragSource = fragPath.c_str();

		GLint result;

		//vert
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);


		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);

			std::cout << "Failed to compile vertex shader! " << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		//frag
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);

			std::cout << "Failed to compile fragment shader! " << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		//link shaders to program
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;

	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}


	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}
} } } }

#endif