#pragma once
#include <glew\glew.h>
#include <GLFW\glfw3.h>

void reshape(GLFWwindow* window, int width, int height);
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void display();
void update();