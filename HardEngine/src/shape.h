#ifndef SHAPE_H
#define SHAPE_H
#include "entity2D.h"
#include "shader.h"
#include "renderer.h"
#include "export.h"

namespace Engine {
	class HARD_ENGINE_API Shape: public Entity2D {
		enum HARD_ENGINE_API ShapeType {
			Triangle,
			Quad
		};
	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		float _triVertices[18] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int _triIndices[3] = {
			0, 1, 2
		};

		float _quadVertices[24] = {
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
		};

		unsigned int _quadIndices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		void GenerateVAO();
		void GenerateVBO();
		void GenerateEBO();
		void BindVAO();
		void BindVBO(float* vertices, int verticesAmount);
		void BindEBO(unsigned int* indices, int indicesAmount);
		void UnbindShapeBuffers();
		void DeleteShapeBuffers();

		Renderer* _renderer;
		Shader _shader;
		ShapeType _type;

	public:
		Shape();
		Shape(ShapeType type);
		~Shape();
		void InitShape();
		void SetShader(Shader shader);
		void UseRenderer(Renderer* renderer);
		void SetColor(float r, float g, float b);
		void Draw();
	};
}

#endif