#include "base_game.h"
#include "GL/glew.h" //se debe incluir primero glew, este incluye encabezados de OpenGL
#include "GLFW/glfw3.h" //se debe incluir segundo glfw
#include "gtc/type_ptr.hpp"
#include "vec3.hpp"
#include "mat4x4.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

using namespace Engine;

GLFWwindow* window;

//unsigned int VBO, VAO, EBO = 0; //Pasar a clase shape, los datos de vertices, indices, etc son parte de cada shape que se instancien en el juego

//unsigned int texture; //pasar a texture importer cuando este lista la clase

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

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

void BaseGame::StartEngine() {
    InitEngine();
    UpdateEngine();
    UnloadEngine();
}

void BaseGame::InitEngine() {
    _window->CreateWindow(800, 600, "HardEngine");
    _renderer->InitGLEW();
    shaders.Create("..//HardEngine//src//vertexShader.vs", "..//HardEngine//src//fragmentShader.fs");
    textureShaders.Create("..//HardEngine//src//vertexTextureShader.vs", "..//HardEngine//src//fragmentTextureShader.fs");
    StartTriangleData();
    InitGame();
}

void BaseGame::StartTriangleData() {
    glEnable(GL_DEPTH_TEST);
    //triangle shape
    //float triVertices[18] = {
    //    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    //};
    //
    //unsigned int triIndices[3] = {
    //    0, 1, 2
    //};
    //
    ////quad shape con UVs
    //float quadVertices[32] = {
    //    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    //    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    //   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    //   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f
    //};
    //
    //unsigned int quadIndices[6] = {
    //    0, 1, 3,
    //    1, 2, 3
    //};
    //
    ////creando el vertex buffer object
    ////unsigned int VBO, VAO, EBO;
    //_renderer->GenerateVAO(VAO);
    //_renderer->GenerateVBO(VBO);
    //_renderer->GenerateEBO(EBO);
    //_renderer->BindVAO(VAO);
    //_renderer->BindVBO(VBO, quadVertices, 32); //Cuando se pase a la clase Shape no hardcodear la cantidad de indices, si pasamos mal la cantidad de indices puede que no dibuje
    //_renderer->BindEBO(EBO, quadIndices, 6); //Cuando se pase a la clase Shape no hardcodear la cantidad de indices, si pasamos mal la cantidad de indices puede que no dibuje
    //
    ////Pasar los attrib pointer a shader y crearlos dependiendo si hay textura o no
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //pasar a la clase shader cuando este
    //glEnableVertexAttribArray(0); //pasar a la clase shader cuando este
    //
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//El ultimo parametro indica desde donde se debe empezar a leer para interpretar los atributos en este caso de color.
    //glEnableVertexAttribArray(1);
    //
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//
    //glEnableVertexAttribArray(2);
    //
    //glGenTextures(1, &texture); //toma cuantas texturas queremos generar y la almacenamos en una matriz de unsigned int.
    //glBindTexture(GL_TEXTURE_2D, texture); //enlazamos la textura en un objeto de textura
    //
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    //stbi_set_flip_vertically_on_load(true);
    //
    //int width;
    //int height;
    //int nrChannels;
    //
    //unsigned char* data = stbi_load("..//HardEngine//resources//HG-logo2.jpg", &width, &height, &nrChannels, 0);
    //
    //if (data)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //generamos la textura propiamente dicha y especificamos la textura
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture" << std::endl;
    //}
    //stbi_image_free(data); //como todo objeto enlazado y utilizado hay que liberarlo de la memoria

    shaders.Use();
    textureShaders.Use();

    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);

    //esto es lo mismo que unbind buffers de renderer
   // _renderer->UnbindBuffers();
}

void BaseGame::UpdateEngine() {
    while (!glfwWindowShouldClose(_window->GetWindow())) {
        input(_window->GetWindow());
        _renderer->StartFrame(0.5f, 0.5f, 0.5f);
        
        UpdateGame();

        //projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

        //pasar a shader a la parte de Draw
        //// note that we're translating the scene in the reverse direction of where we want to move
        
        unsigned int modelLoc = glGetUniformLocation(shaders.GetID(), "model");
        unsigned int viewLoc = glGetUniformLocation(shaders.GetID(), "view");
        unsigned int projectionLoc = glGetUniformLocation(shaders.GetID(), "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //glBindTexture(GL_TEXTURE_2D, texture);
        shaders.Use();
        textureShaders.Use();
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //_renderer->BindVAO(VAO);
        //_renderer->Draw();

        _renderer->EndFrame(_window->GetWindow());
    }
}

void BaseGame::UnloadEngine() {
    UnloadGame();
    //_renderer->DeleteBuffers(VAO, VBO, EBO);
    shaders.DeleteProgram();
    textureShaders.DeleteProgram();
    glfwTerminate();
}

void BaseGame::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}