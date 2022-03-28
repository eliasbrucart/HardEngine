#ifndef RENDERER_H
#define RENDERER_H

#include "export.h"

struct GLFWwindow;

namespace Engine {

	class HARD_ENGINE_API Renderer {
	private:
	public:
		Renderer();
		~Renderer();
		void InitGLEW();
		void StartFrame(float r, float g, float b);
		void EndFrame(GLFWwindow* window);
		void GenerateVAO(unsigned int& vao);
		void GenerateVBO(unsigned int& vbo);
		void GenerateEBO(unsigned int& ebo);
		void BindVAO(unsigned int& vao);
		void BindVBO(unsigned int& vbo, float* vertices, int verticesAmount);
		void BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmount);
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
		void UnbindBuffers();
		void Draw(unsigned int &vao, unsigned int &vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmount);
		void Draw();
	};
}
#endif