#include <iostream>

#include "main.h"
#include "resource_manager.h"

int main()
{
    using namespace std;

    // Initialize GLFW and set required options
    cout << "Initializing GLFW, setting required options..." << endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a new window and set it as current context
    cout << "Creating a new window and setting it as current context..." << endl;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Enable GLEW experimental and initialize GLEW to setup OpenGL function pointers
    cout << "Initializing GLEW..." << endl;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }
    glGetError(); // Get GLEW's error to avoid confusing it with our application

    // Register callbacks
    cout << "Registering callbacks..." << endl;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Retrieve the dependant-platform width and height and set the viewport
    cout << "Setting viewport..." << endl;
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

    glViewport(0, 0, viewportWidth, viewportHeight);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    cout << "Initializing game..." << endl;
    game = Game(viewportWidth, viewportHeight);
    game.Init();

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    game.State = GAME_ACTIVE;

    // Enter the game loop
    cout << "Game started!" << endl;

    // Keep in mind that anything that doesn't change (i.e. a position)
    // can be outside the game loop for a huge performance improvement.
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        // Poll events such as key pressed or mouse moved
        glfwPollEvents();

        // Manage user input
        game.ProcessInput(deltaTime);

        // Update game state
        game.Update(deltaTime);

        // Render
        // Clear the color buffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.Render();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key <= 256)
    {
        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, GL_TRUE);
            else
                game.Keys[key] = GL_TRUE;
        }

        else if (action == GLFW_RELEASE)
            game.Keys[key] = GL_FALSE;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }
    GLfloat xoffset = xpos - lastMouseX;
    GLfloat yoffset = lastMouseY - ypos; // Reversed since y coordinates range from bottom to top

    lastMouseX = xpos;
    lastMouseY = ypos;

    game.MouseXOffset += xoffset;
    game.MouseYOffset += yoffset;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessZoom(yoffset);
}