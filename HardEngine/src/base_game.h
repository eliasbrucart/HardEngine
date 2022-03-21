#ifndef BASE_GAME_H
#define BASE_GAME_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "window.h"
#include "renderer.h"
#include "shader.h"

#include "export.h"

namespace Engine {

	class HARD_ENGINE_API BaseGame {
	private:
		Window* _window;
		Renderer* _renderer;
		Shader shaders;
	public:
		BaseGame();
		~BaseGame();
		void InitEngine();
		void StartTriangleData(); //esto va a pertencer a la clase renderer ya que tiene que ver con el dibujado
		void UpdateEngine();
		void UnloadEngine();
		void input(GLFWwindow* window);
	};
}

#endif