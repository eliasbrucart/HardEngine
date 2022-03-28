#include "shape.h"

using namespace Engine;

Shape::Shape() : Entity2D() {
	_type = ShapeType::Triangle;
	_renderer = NULL;
}

Shape::Shape(ShapeType type) {
	_type = type;
}

Shape::~Shape() {
	UnbindShapeBuffers();
	DeleteShapeBuffers();
}

void Shape::GenerateVAO() {
	_renderer->GenerateVAO(_vao);
}

void Shape::GenerateVBO() {
	_renderer->GenerateVBO(_vbo);
}

void Shape::GenerateEBO() {
	_renderer->GenerateEBO(_ebo);
}

void Shape::BindVAO() {
	_renderer->BindVAO(_vao);
}

void Shape::BindVBO(float* vertices, int verticesAmount) {
	_renderer->BindVBO(_vbo, vertices, verticesAmount);
}

void Shape::BindEBO(unsigned int* indices, int indicesAmount) {
	_renderer->BindEBO(_ebo, indices, indicesAmount);
}

void Shape::UnbindShapeBuffers() {
	_renderer->UnbindBuffers();
}

void Shape::DeleteShapeBuffers() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
}

void Shape::InitShape() {
	GenerateVAO();
	GenerateVBO();
	GenerateEBO();
	BindVAO();
	if (_type == ShapeType::Triangle) {
		BindVBO(_triVertices, 18);
		BindEBO(_triIndices, 3);
	}
	else if (_type == ShapeType::Quad) {
		BindVBO(_quadVertices, 24);
		BindEBO(_quadIndices, 6);
	}
}

void Shape::SetShader(Shader shader) {
	_shader = shader;
}

void Shape::UseRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Shape::SetColor(float r, float g, float b) {
	//luego
}

void Shape::Draw() {
	if(_type == ShapeType::Triangle)
		_renderer->Draw(_vao, _vbo, _triVertices, 18, _triIndices, 3);
	else if (_type == ShapeType::Quad)
		_renderer->Draw(_vao, _vbo, _quadVertices, 24, _quadIndices, 6);
}