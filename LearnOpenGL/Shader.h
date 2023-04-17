#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

class Shader
{
public:
	Shader(const char* vertexPath,const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	
	unsigned int programID;
	void useProgram();

private:
	void checkCompileErrors(unsigned int ID,std::string type);

};

	