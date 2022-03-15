#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "window.h"

#include <iostream>

using namespace Engine;

Window::Window() {
    _width = 800;
    _height = 600;
    _window = NULL;
}

Window::Window(int width, int height) {
	_width = width;
	_height = height;
    _window = NULL;
}

Window::~Window() {

}

void Window::CreateWindow(int width, int height, const char* windowName) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    _window = glfwCreateWindow(width, height, windowName, NULL, NULL);

    //if (!glfwInit())
    //    return -1;

    if (_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }

    windowReSizeCallback(_window, width, height);

    glfwMakeContextCurrent(_window);
}

GLFWwindow* Window::GetWindow() {
	return _window;
}

void Window::SetWidth(int width) {
	_width = width;
}

int Window::GetWidth() {
	return _width;
}

void Window::SetHeight(int height) {
	_height = height;
}

int Window::GetHeight() {
	return _height;
}

void Window::windowReSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}