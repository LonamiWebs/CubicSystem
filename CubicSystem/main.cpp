// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>

#include "main.h"
#include "shader.h"
#include "camera.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    using namespace std;
    using namespace glm;

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

    // Register callbacks
    cout << "Registering callbacks..." << endl;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Enable GLEW experimental and initialize GLEW to setup OpenGL function pointers
    cout << "Initializing GLEW..." << endl;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    // Retrieve the dependant-platform width and height and set the viewport
    cout << "Setting viewport..." << endl;
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

    glViewport(0, 0, viewportWidth, viewportHeight);
    glEnable(GL_DEPTH_TEST);

    // Initialize our shader
    cout << "Loading shaders..." << endl;
    Shader shader("../CubicSystem/shaders/shader.vert", "../CubicSystem/shaders/shader.frag");
    cout << "Loading lamp shaders..." << endl;
    Shader lampShader("../CubicSystem/shaders/shader.vert", "../CubicSystem/shaders/lamp_shader.frag");

    // Set up vertex data and buffers
    cout << "Setting up vertex data and buffers.." << endl;
    GLfloat vertices[] = {
        // Positions          Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint containerVAO, VBO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    // Bind our Vertex Array Object first, then bind and set the vertex buffers and attribute pointers
    glBindVertexArray(containerVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // How to interpret vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind for safety reasons
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Do the same for the light
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // No need to copy the data again, as we already did it before

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vec3 cubePositions[] = {
        vec3( 0.0f,  0.0f,  0.0f),
        vec3( 2.0f,  5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3( 2.4f, -0.4f, -3.5f),
        vec3(-1.7f,  3.0f, -7.5f),
        vec3( 1.3f, -2.0f, -2.5f),
        vec3( 1.5f,  2.0f, -2.5f),
        vec3( 1.5f,  0.2f, -1.5f),
        vec3(-1.3f,  1.0f, -1.5f)
    };

    // Enter the game loop
    cout << "Game started!" << endl;

    // Keep in mind that anything that doesn't change (i.e. a position)
    // can be outside the game loop for a huge performance improvement.
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - last.Frame;
        last.Frame = currentTime;

        // Poll events such as key pressed or mouse moved
        glfwPollEvents();
        do_movement();

        // Render
        // Clear the color buffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        GLfloat radius = 4.0f;
        GLfloat lightSpeed = 2.0f; // No, not that light speed
        vec3 lightPos;
        lightPos.x = cos(glfwGetTime() * lightSpeed) * radius;
        lightPos.y = 1.2f;
        lightPos.z = sin(glfwGetTime() * lightSpeed) * radius;

        // Draw our objects
        shader.Use();
        // cyan rubber 	 	 		 	 	 	 	 	
        glUniform3f(shader.GetUniform("material.ambient"), 0.0f, 0.05f, 0.05f);
        glUniform3f(shader.GetUniform("material.diffuse"), 0.4f, 0.5f, 0.5f);
        glUniform3f(shader.GetUniform("material.specular"), 0.04f, 0.7f, 0.7f);
        glUniform1f(shader.GetUniform("material.shininess"), 10.0f);

        glUniform3f(shader.GetUniform("light.position"), lightPos.x, lightPos.y, lightPos.z);

        glUniform3f(shader.GetUniform("light.ambient"), 1.0f, 1.0f, 1.0f);
        glUniform3f(shader.GetUniform("light.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(shader.GetUniform("light.specular"), 1.0f, 1.0f, 1.0f);

        glUniform1f(shader.GetUniform("light.constant"), 1.0f);
        glUniform1f(shader.GetUniform("light.linear"), 0.9f);
        glUniform1f(shader.GetUniform("light.quadratic"), 0.032f);

        glUniform3f(shader.GetUniform("viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        // Create camera transformations
        mat4 view = camera.GetViewMatrix();
        mat4 projection = perspective(camera.Zoom, viewportWidth / (GLfloat)viewportHeight, 0.1f, 100.0f);

        // Set them and draw
        glUniformMatrix4fv(shader.GetUniform("projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(shader.GetUniform("view"), 1, GL_FALSE, value_ptr(view));

        glBindVertexArray(containerVAO);
        for (int i = 0; i < 10; i++)
        {
            mat4 model;
            model = translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = rotate(model, angle, vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(shader.GetUniform("model"), 1, GL_FALSE, value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        // Draw lamp
        lampShader.Use();

        glUniformMatrix4fv(lampShader.GetUniform("projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(lampShader.GetUniform("view"), 1, GL_FALSE, value_ptr(view));

        mat4 model;
        model = translate(model, lightPos);
        model = scale(model, vec3(0.2f));
        glUniformMatrix4fv(lampShader.GetUniform("model"), 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up resources
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void do_movement()
{
    if (keys[GLFW_KEY_W])
        camera.ProcessMovement(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessMovement(BACKWARD, deltaTime);

    if (keys[GLFW_KEY_A])
        camera.ProcessMovement(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessMovement(RIGHT, deltaTime);


    if (keys[GLFW_KEY_KP_ADD])
        camera.ProcessZoom(+0.1f);
    if (keys[GLFW_KEY_KP_SUBTRACT])
        camera.ProcessZoom(-0.1f);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key <= 512)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;

        else if (action == GLFW_RELEASE)
            keys[key] = false;

        switch (key)
        {
            // Options
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);

            break;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        last.MouseX = xpos;
        last.MouseY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - last.MouseX;
    GLfloat yoffset = last.MouseY - ypos; // Reversed since y coordinates range from bottom to top

    last.MouseX = xpos;
    last.MouseY = ypos;

    camera.ProcessEyeMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessZoom(yoffset);
}