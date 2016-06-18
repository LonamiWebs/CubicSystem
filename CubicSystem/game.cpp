#include "game.h"
#include "resource_manager.h"

#include "camera.h"
#include "cube_renderer.h"

Camera camera;
CubeRenderer* renderer;

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) { }

Game::~Game()
{
}

void Game::Init()
{
    // Load shaders
    Shader shader = ResourceManager::LoadShader(
        "../CubicSystem/shaders/shader.vert",
        "../CubicSystem/shaders/shader.frag", nullptr, "block");

    // Configure shaders
    shader.SetInteger("image", 0, GL_TRUE); // And use shader
    glm::mat4 projection = glm::perspective(camera.Zoom, Width / (GLfloat)Height, 0.1f, 100.0f);
    shader.SetMatrix4("projection", projection);

    // Set renderer specific fields
    renderer = new CubeRenderer(shader);

    // Load textures
    ResourceManager::LoadTexture("../CubicSystem/images/stone.png", GL_FALSE, "stone");
}

void Game::ProcessInput(GLfloat dt)
{
    // Movement
    if (Keys[GLFW_KEY_W])
        camera.ProcessMovement(FORWARD, dt);
    if (Keys[GLFW_KEY_S])
        camera.ProcessMovement(BACKWARD, dt);
    if (Keys[GLFW_KEY_A])
        camera.ProcessMovement(LEFT, dt);
    if (Keys[GLFW_KEY_D])
        camera.ProcessMovement(RIGHT, dt);

    // Camera
    camera.ProcessEyeMovement(MouseXOffset, MouseYOffset);
    MouseXOffset = MouseYOffset = 0.0f; // TODO ^ MOVEMENT ISN'T SMOOTH


    if (Keys[GLFW_KEY_KP_ADD])
        camera.ProcessZoom(+0.1f);
    if (Keys[GLFW_KEY_KP_SUBTRACT])
        camera.ProcessZoom(-0.1f);
}

void Game::Update(GLfloat dt)
{
    ResourceManager::GetShader("block").SetMatrix4("view", camera.GetViewMatrix(), GL_TRUE);
}

void Game::Render()
{
    renderer->DrawCube(ResourceManager::GetTexture("stone"), glm::vec3(0.0f, 0.0f, 0.0f));
}


