#pragma once

// Window dimensions and title
const GLuint WIDTH = 800, HEIGHT = 600;
const GLchar* TITLE = "Cubic System";

// Shaders
const GLchar* vertexShaderSource =
"#version 330 core\n"

"layout (location = 0) in vec3 position;\n"

"void main()\n"
"{\n"
"    gl_Position = vec4(position, 1.0);\n"
"}";

const GLchar* fragmentShaderSource =
"#version 330 core\n"

"out vec4 color;\n"

"void main()\n"
"{\n"
"    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}";

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Thanks a lot to learnopengl.com \(^-^)/