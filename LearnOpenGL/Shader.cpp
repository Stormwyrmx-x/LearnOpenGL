#include "Shader.h"


Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	std::ifstream vertexFileStream;
	std::ifstream fragmentFileStream;
	std::stringstream vertexStringStream;
	std::stringstream fragmentStringStream;

	// ensure ifstream objects can throw exceptions
	vertexFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//读取路径，先变成二进制，再变成string，再转化为char*(OPENGL只吃char*)
		vertexFileStream.open(vertexPath);
		fragmentFileStream.open(fragmentPath);
		if (!vertexFileStream.is_open() || !fragmentFileStream.is_open())
		{
			throw std::exception("failed to open file");
		}
		vertexStringStream<<vertexFileStream.rdbuf();
		fragmentStringStream<<fragmentFileStream.rdbuf();
		vertexString=vertexStringStream.str();
		fragmentString=fragmentStringStream.str();
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//编写shader
		unsigned int vertex, fragment;

		vertex=glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//编写program
		programID=glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);
		checkCompileErrors(programID, "PROGRAM");

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::useProgram()
{
	glUseProgram(programID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << type <<" shader compile error " << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "program linking error " << infoLog << std::endl;
		}
	}
}
