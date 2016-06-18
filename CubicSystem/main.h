#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"

// Window dimensions and title
const GLuint WIDTH = 800, HEIGHT = 600;
const GLchar* TITLE = "Cubic System";

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Fields
Game game(WIDTH, HEIGHT);

// Thanks a lot to learnopengl.com \(^-^)/