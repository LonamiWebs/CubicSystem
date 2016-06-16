#pragma once

// Window dimensions and title
const GLuint WIDTH = 800, HEIGHT = 600;
const GLchar* TITLE = "Cubic System";

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void do_movement();

// Fields
bool firstMouse = true;
bool keys[512];

GLfloat deltaTime;

// Keep track of the last frame values
struct Last
{
public:
    GLfloat Frame;
    GLfloat MouseX, MouseY;

    Last()
    {
        Frame = 0;
        MouseX = 400;
        MouseY = 300;
    }
} last;

// Thanks a lot to learnopengl.com \(^-^)/