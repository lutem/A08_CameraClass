#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OpenGL.h"
#include "ShaderHelpers.h"
using namespace std;

GLuint VBO;
GLuint VAO;
const GLsizei numberOfVertices = 3;
const GLsizei numberOfValues = numberOfVertices * 2;

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL App", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	init();
	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void init()
{
	GLuint shaderProgramIndex;
	shaderProgramIndex = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (shaderProgramIndex != 0)
		glUseProgram(shaderProgramIndex);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLfloat vertexBufferData[numberOfValues] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		0.0f, 1.0f

	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);

	glClearColor(0.5f, 0.5f, 1.0f, 0.f);
}

void update()
{
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	
	glFlush();
}