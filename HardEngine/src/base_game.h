#ifndef BASE_GAME_H
#define BASE_GAME_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "window.h"

#include "export.h"

namespace Engine {

	class HARD_ENGINE_API BaseGame {
	private:
		Window* _window;
	public:
		BaseGame();
		~BaseGame();
		void InitEngine();
		void StartEngine();
		//void CreateWindow(int width, int height, const char* windowName); //esto va a pertencer a la claseWindow
		void StartGLEWContext(); //esto va a pertencer a la clase renderer ya que tiene que ver con el dibujado
		void UpdateEngine();
		void UnloadEngine();
		void input(GLFWwindow* window);
		void windowReSizeCallback(GLFWwindow* window, int width, int height);
	};
}

#endif