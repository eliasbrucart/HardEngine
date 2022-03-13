#include <iostream>
#include "GL/glew.h" //se debe incluir primero glew, este incluye encabezados de OpenGL
#include "GLFW/glfw3.h" //se debe incluir segundo glfw
using namespace std;

void windowReSizeCallback(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    int windowWidth = 800;
    int windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "HardEngine", NULL, NULL);

    //if (!glfwInit())
    //    return -1;

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, windowReSizeCallback);

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        input(window);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void windowReSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}