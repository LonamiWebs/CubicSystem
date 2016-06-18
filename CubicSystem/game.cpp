#include "game.h"

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) { }

Game::~Game()
{
}

void Game::Init()
{

}

#include "camera.h"
Camera camera;

void Game::ProcessInput(GLfloat dt)
{
    if (Keys[GLFW_KEY_W])
        camera.ProcessMovement(FORWARD, dt);
    if (Keys[GLFW_KEY_S])
        camera.ProcessMovement(BACKWARD, dt);

    if (Keys[GLFW_KEY_A])
        camera.ProcessMovement(LEFT, dt);
    if (Keys[GLFW_KEY_D])
        camera.ProcessMovement(RIGHT, dt);


    if (Keys[GLFW_KEY_KP_ADD])
        camera.ProcessZoom(+0.1f);
    if (Keys[GLFW_KEY_KP_SUBTRACT])
        camera.ProcessZoom(-0.1f);
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
}


