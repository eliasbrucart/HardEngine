#include "base_game.h"
#include "GL/glew.h" //se debe incluir primero glew, este incluye encabezados de OpenGL
#include "GLFW/glfw3.h" //se debe incluir segundo glfw

#include <iostream>

using namespace Engine;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

GLFWwindow* window;

unsigned int shaderProgram; //Pasar a clase Shader cuando este
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
}

void BaseGame::StartEngine() {
	
}

void BaseGame::StartGLEWContext() {
    //compilando el shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); //Al crear el shader hay que especificar el tipo del mismo, en este caso el vertex shader. Lo almacenamos en nuestra variable de shader.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Una vez creado el shader tenemos que especificarle que codigo es el que contendra, le pasamos vertexShaderSource que contiene el codigo fuente del vertex shader
    glCompileShader(vertexShader); //Compilamos el shader, luego hay que linkearlo al programa principal para que sea ejecutado en la GPU, lo linkeamos generando un objeto de tipo programa.

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //compilando el shader (seguimos los mismos pasos que para compilar el vertex shader)
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);;
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Creando objeto de tipo shader program
    //unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); //Para poder usar los shaders debemos crear los objetos de programa y asi linkearlos con el main program y sean utilizados.
    glAttachShader(shaderProgram, vertexShader); //Enlazamos el objeto de tipo vertex shader a el objeto de tipo programa.
    glAttachShader(shaderProgram, fragmentShader); //Enlazamos el objeto de tipo fragment shader a el objeto de tipo programa.
    glLinkProgram(shaderProgram);
    //glUseProgram(shaderProgram); //Habilitamos el uso del objeto de tipo programa que esta enlazado con los objetos de shader que contienen el vertex y fragment shader
    //asi podremos ejecutar los dos shaders previamente programados.

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
        glUseProgram(shaderProgram); //pasar a la clase shader cuando este
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        _renderer->BindVAO(VAO);
        _renderer->Draw();

        _renderer->EndFrame(_window->GetWindow());
    }
}

void BaseGame::UnloadEngine() {
    _renderer->DeleteBuffers(VAO, VBO, EBO);
    glDeleteProgram(shaderProgram); //pasar a shader
    glfwTerminate();
}

void BaseGame::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}