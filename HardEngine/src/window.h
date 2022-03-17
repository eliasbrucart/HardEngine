#ifndef WINDOW_H
#define WINDOW_H

#include "export.h"

struct GLFWwindow;

namespace Engine {
	class HARD_ENGINE_API Window {
	private:
		GLFWwindow* _window;
		int _width;
		int _height;
	public:
		Window();
		Window(int width, int height);
		~Window();
		void CreateWindow(int width, int height, const char* windowName);
		GLFWwindow* GetWindow();
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
	};
}

#endif