#include "base_game.h"
#include "GL/glew.h" //se debe incluir primero glew, este incluye encabezados de OpenGL
#include "GLFW/glfw3.h" //se debe incluir segundo glfw
#include "gtc/type_ptr.hpp"
#include "vec3.hpp"
#include "mat4x4.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

#include <iostream>

using namespace Engine;

GLFWwindow* window;

unsigned int VBO, VAO, EBO = 0; //Pasar a clase shape, los datos de vertices, indices, etc son parte de cada shape que se instancien en el juego

BaseGame::BaseGame() {
    _window = new Window(800, 600);
    _renderer = new Renderer();
}

BaseGame::~BaseGame() {
    if (_window != NULL) {
        delete _window;
        _window = NULL;
    }
    if (_renderer != NULL) {
        delete _renderer;
        _renderer = NULL;
    }
}

void BaseGame::InitEngine() {
    _window->CreateWindow(800, 600, "HardEngine");
    _renderer->InitGLEW();
    shaders.Create("src//vertexShader.vs", "src//fragmentShader.fs");
    StartTriangleData();
}

void BaseGame::StartTriangleData() {

    float vertices[18] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    //creando el vertex buffer object
    //unsigned int VBO, VAO, EBO;
    _renderer->GenerateVAO(VAO);
    _renderer->GenerateVBO(VBO);
    _renderer->GenerateEBO(EBO);
    _renderer->BindVAO(VAO);
    _renderer->BindVBO(VBO, vertices, 18); //Cuando se pase a la clase Shape no hardcodear la cantidad de indices, si pasamos mal la cantidad de indices puede que no dibuje
    _renderer->BindEBO(EBO, indices, 3); //Cuando se pase a la clase Shape no hardcodear la cantidad de indices, si pasamos mal la cantidad de indices puede que no dibuje

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //pasar a la clase shader cuando este
    glEnableVertexAttribArray(0); //pasar a la clase shader cuando este

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//El ultimo parametro indica desde donde se debe empezar a leer para interpretar los atributos en este caso de color.
    glEnableVertexAttribArray(1);

    //esto el lo mismo que unbind buffers de renderer
    _renderer->UnbindBuffers();
}

void BaseGame::UpdateEngine() {
    while (!glfwWindowShouldClose(_window->GetWindow())) {
        input(_window->GetWindow());
        _renderer->StartFrame(0.5f, 0.5f, 0.5f);

        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUseProgram(shaderProgram); //pasar a la clase shader cuando este
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shaders.GetID(), "model");
        unsigned int viewLoc = glGetUniformLocation(shaders.GetID(), "view");
        unsigned int projectionLoc = glGetUniformLocation(shaders.GetID(), "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        shaders.Use();
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        _renderer->BindVAO(VAO);
        _renderer->Draw();

        _renderer->EndFrame(_window->GetWindow());
    }
}

void BaseGame::UnloadEngine() {
    _renderer->DeleteBuffers(VAO, VBO, EBO);
    shaders.DeleteProgram();
    glfwTerminate();
}

void BaseGame::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}