#include "GL/glew.h" //se debe incluir primero glew, este incluye encabezados de OpenGL
#include "GLFW/glfw3.h" //se debe incluir segundo glfw
#include <iostream>

void windowReSizeCallback(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    int windowWidth = 800;
    int windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "HardEngine", NULL, NULL);

    if (!glfwInit())
        return -1;

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetFramebufferSizeCallback(window, windowReSizeCallback);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return false;
    }
    
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
    unsigned int shaderProgram;
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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };


    //creando el vertex buffer object
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //esto genera el objeto de buffer de vertices, se debe hacer una sola vez
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Reservamos memoria para el buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Le especificamos al buffer cual es el contenido que tendra y como seran usados estos datos al momento de dibujar.

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        input(window);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

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