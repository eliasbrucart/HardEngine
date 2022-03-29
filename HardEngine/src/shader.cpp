#include"shader.h"
#include "GL/glew.h"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace Engine;

Shader::Shader() {
	_id = 0;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

}

Shader::~Shader() {

}

void Shader::Create(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		try {
			std::stringstream vertexShaderStream;
			std::stringstream fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			try {
				vertexShaderFile.close();
				fragmentShaderFile.close();

				vertexCode = vertexShaderStream.str();
				fragmentCode = fragmentShaderStream.str();
			}
			catch (std::ifstream::failure e) {
				std::cout << "ERROR::CLOSE_FILE" << std::endl;
			}
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::FAIL_READ_SHADER" << std::endl;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned int vertex;
	unsigned int fragment;
	int success;
	char infoLog[512];

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);//Al crear el shader hay que especificar el tipo del mismo, en este caso el vertex shader. Lo almacenamos en nuestra variable de shader.
	glCompileShader(vertex);//Compilamos el shader, luego hay que linkearlo al programa principal para que sea ejecutado en la GPU, lo linkeamos generando un objeto de tipo programa.

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	_id = glCreateProgram();//Para poder usar los shaders debemos crear los objetos de programa y asi linkearlos con el main program y que sean utilizados por el main program.
	glAttachShader(_id, vertex);//Enlazamos el objeto de tipo vertex shader a el objeto de tipo programa.
	glAttachShader(_id, fragment);//Enlazamos el objeto de tipo fragment shader a el objeto de tipo programa.
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::SetVertexPosition(const char* nameAttrib, int dataSize) {
	unsigned int posAttribute = glGetAttribLocation(_id, nameAttrib);
	CreateAttribPointer(0, 3, dataSize, 0);
}

void Shader::SetVertexColor(const char* nameAttrib, int dataSize) {
	unsigned int posAttribute = glGetAttribLocation(_id, nameAttrib);
	CreateAttribPointer(1, 3, dataSize, 3);
}

void Shader::CreateAttribPointer(unsigned int attributeID, int dataAmount, int dataSize, int dataPos) {
	glVertexAttribPointer(attributeID, dataAmount, GL_FLOAT, GL_FALSE, dataSize * sizeof(float), (void*)(sizeof(float) * dataPos)); //pasar a la clase shader cuando este
	glEnableVertexAttribArray(attributeID);
}


void Shader::Use() {
	glUseProgram(_id);//Habilitamos el uso del objeto de tipo programa que esta enlazado con los objetos de shader que contienen el vertex y fragment shader
    ////asi podremos ejecutar los dos shaders previamente programados.
}

int Shader::GetID() {
	return _id;
}

void Shader::DeleteProgram() {
	glDeleteProgram(_id);
}