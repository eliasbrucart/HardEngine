#ifndef BASE_GAME_H
#define BASE_GAME_H

#include "export.h"
#include "window.h"
#include "renderer.h"
#include "shader.h"


namespace Engine {
	class HARD_ENGINE_API BaseGame {
	private:
		Window* _window;
		Renderer* _renderer;
	protected:
		Shader shaders;
		void InitEngine();
		void StartTriangleData(); //esto va a pertencer a la clase renderer ya que tiene que ver con el dibujado
		void UpdateEngine();
		void UnloadEngine();
		void input(GLFWwindow* window);
	public:
		BaseGame();
		~BaseGame();
		void StartEngine();
		virtual void InitGame() = 0;
		virtual void UpdateGame() = 0;
		virtual void UnloadGame() = 0;
	};
}

#endif