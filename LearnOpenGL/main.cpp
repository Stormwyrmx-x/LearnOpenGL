#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void processInput(GLFWwindow*);
void frame_buffer_size_callback(GLFWwindow*,int,int);

int main()
{
	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);//by using the compatible profile,we can use 固定渲染管线

	
	//open glfw window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "exercise1", NULL, NULL);
	if (window == NULL)
	{
		printf("failed to create window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	//When the window is first displayed,framebuffer_size_callback gets called as well with the resulting window dimensions.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//剔除背面
	glEnable(GL_DEPTH_TEST);

	//init glew
	glewExperimental = true;
	if (glewInit( ) != GLEW_OK)
	{
		printf("failed to init glew!");
		return -1;
	}

	//create VAO and VBO and EBO
	//bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices , GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glEnableVertexArrayAttrib(VAO, 0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//The last element buffer object that gets bound while a VAO is bound, is stored as the VAO's element buffer object. 
	//也就是说，VAO BIND 要在 EBO BIND 之前
	

	// create two textures
	unsigned int TextureBuffer[3];
	glGenTextures(3, TextureBuffer);

	//绑定并传送第一张图片contain.jpg
	//glActiveTexture(GL_TEXTURE0);//This location of a texture is more commonly known as a texture unit.
	glBindTexture(GL_TEXTURE_2D, TextureBuffer[0]);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);// tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data0 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data0)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture0" << std::endl;
	}
	stbi_image_free(data0);

	//绑定并传送第二章图片awesomeface.png
	//glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture1" << std::endl;
	}
	stbi_image_free(data1);
	
	//绑定并传送第三章图片jinzhengen.jpg
	glBindTexture(GL_TEXTURE_2D, TextureBuffer[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("jinzhengen.jpg", &width, &height,&nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture2" << std::endl;
	}
	stbi_image_free(data2);

	//create shader
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	//set uniform
	myShader->useProgram();
	glUniform1i(glGetUniformLocation(myShader->programID, "Texture0"), 0);
	glUniform1i(glGetUniformLocation(myShader->programID, "Texture1"), 1);
	glUniform1i(glGetUniformLocation(myShader->programID, "Texture2"), 2);
	
	
	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//render command here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureBuffer[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TextureBuffer[1]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, TextureBuffer[2]);
		
		myShader->useProgram();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	
		//create transformations
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(i*(float)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 viewMatrix = glm::mat4(1.0f);
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -3.0f));
			glm::mat4 projectionMatrix = glm::mat4(1.0f);
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
			glUniformMatrix4fv(glGetUniformLocation(myShader->programID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(myShader->programID, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(glGetUniformLocation(myShader->programID, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			
			
			
			
			/*float timeValue = glfwGetTime();
			float blueValue = (sin(timeValue*i) / 2.0f) + 0.5f;
			float redValue = (cos(timeValue*i) / 2.0f) + 0.5f;
			float greenValue = (cos(timeValue * 2) / 2.0f) + 0.5f;
			int colorLocation = glGetUniformLocation(myShader->programID, "jinzhengenColor");
			glUniform4f(colorLocation, redValue, greenValue, blueValue, 1.0f);*/


			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3((sin)(glfwGetTime()), (sin)(glfwGetTime()), 0));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0));
		//trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
		//trans = glm::translate(trans, glm::vec3(0, 0, 0.3f));
		/*trans = glm::rotate(trans,glm::radians(180.0f), glm::vec3(1.0f, 0, 0));
		trans = glm::translate(trans, glm::vec3(0, 0.3f, 0));
		glUniformMatrix4fv(glGetUniformLocation(myShader->programID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		*/
		
		

		
		//glBindTexture(GL_TEXTURE_2D, TextureBuffer);

		//init uniform
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		float redValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/

		

		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, redValue, 0.5f, 0.5f, 1.0f);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//The glDrawElements function takes its indices from the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target.

        //drawTriangle();	


		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow*window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);

	}
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
}

//void drawPoint()
//{
//	/* Draw a point */
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glPointSize(2.0f);
//	glBegin(GL_POINTS);
//
//	glColor3f(1.0, 0.0, 0.0);    // Red
//	glVertex2f(0.0f, 0.0f);
//	glVertex2f(0.5f, 0.8f);
//	glEnd();
//}
//void drawLint()
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glLineWidth(2);//设置线段宽度
//	glBegin(GL_LINES);
//	glColor3f(1.0, 0.0, 0.0);
//	glVertex2f(0.8, 1); //定点坐标范围
//
//	glVertex2f(0, -1);
//	glEnd();
//}
//void drawTriangle()
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);
//
//	glColor3f(1.0, 0.0, 0.0);    // Red
//	glVertex3f(0.0, 1.0, 0.0);
//
//	glColor3f(0.0, 1.0, 0.0);    // Green
//	glVertex3f(-1.0, -1.0, 0.0);
//
//	glColor3f(0.0, 0.0, 1.0);    // Blue
//	glVertex3f(1.0, -1.0, 0.0);
//	glEnd();
//}



