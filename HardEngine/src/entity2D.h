#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "mat4x4.hpp"
#include "vec3.hpp"
#include "export.h"

namespace Engine {
	class HARD_ENGINE_API Entity2D {
		//matrices de transformacion

		struct HARD_ENGINE_API Rotation {
			glm::mat4 x;
			glm::mat4 y;
			glm::mat4 z;
		};

		struct HARD_ENGINE_API Model {
			glm::mat4 translate;
			glm::mat4 scale;
			Rotation rotation;
			glm::mat4 trs;
		};
	private:
	protected:
		void UpdateMatrices();
		void UpdateModel();
		Model model;
	public:
		Entity2D();
		~Entity2D();
		void Translate(float x, float y, float z);
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void Scale(float x, float y, float z);
		glm::mat4 GetModel();
	};
}

#endif