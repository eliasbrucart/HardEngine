#include "renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace Engine;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::InitGLEW() {
    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        //return false;
    }
}

void Renderer::StartFrame(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::GenerateVAO(unsigned int& vao) {
    glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
}

void Renderer::GenerateVBO(unsigned int& vbo) {
    glGenBuffers(1, &vbo);
}

void Renderer::GenerateEBO(unsigned int& ebo) {
    glGenBuffers(1, &ebo);
}


void Renderer::BindVAO(unsigned int& vao) {
    glBindVertexArray(vao);
}

void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmount) {
    //glGenBuffers(1, &vbo);//esto genera el objeto de buffer de vertices, se debe hacer una sola vez
    glBindBuffer(GL_ARRAY_BUFFER, vbo);//Reservamos memoria para el buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmount, vertices, GL_STATIC_DRAW);//Le especificamos al buffer cual es el contenido que tendra y como seran usados estos datos al momento de dibujar.
}

void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmount) {
    //glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmount, indices, GL_STATIC_DRAW);
}

void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::UnbindBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void Renderer::Draw(unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmount) {
    BindVAO(vao);
    //Agregar update de buffers de vao y vbo si es necesario

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    UnbindBuffers();
}

void Renderer::Draw() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}