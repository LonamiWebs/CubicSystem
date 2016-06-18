#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU
};

class Game
{
public:
    // State
    GameState State;
    GLboolean Keys[256];
    GLuint Width, Height;

    // Constructor and destructor
    Game(GLuint width, GLuint height);
    ~Game();

    // Initialization
    void Init();

    // Game loop
    void ProcessInput(GLfloat dt); // dt stands for delta time
    void Update(GLfloat dt);
    void Render();
};