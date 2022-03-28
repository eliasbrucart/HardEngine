#ifndef SHADER_H
#define SHADER_H

#include "export.h"

namespace Engine {
	class HARD_ENGINE_API Shader {
	private:
		unsigned int _id;
	public:
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void Create(const char* vertexPath, const char* fragmentPath);
		void Use();
		int GetID();
		void DeleteProgram();
	};
}

#endif