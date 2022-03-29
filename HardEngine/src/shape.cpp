#include "shape.h"

using namespace Engine;

Shape::Shape() : Entity2D() {
	_type = ShapeType::Triangle;
	_renderer = NULL;
}

Shape::Shape(Shader shader, ShapeType type) {
	_type = type;
	_shader = shader;
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
	//_shader.SetVertexPosition("aPos", 6);
	//_shader.SetVertexColor("aColor", 6);
	_renderer->CreateAttribPointer(0, 3, 6, 0); //attrib pointer para posicion
	_renderer->CreateAttribPointer(1, 3, 6, 3); //attrib pointer para color
}

void Shape::SetShader(Shader shader) {
	_shader = shader;
}

void Shape::UseRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Shape::SetColor(glm::vec3 color) {
	if (_type == Engine::ShapeType::Triangle) {
		_triVertices[3] = color.x;  _triVertices[4] = color.y;  _triVertices[5] = color.z;
		_triVertices[9] = color.x; _triVertices[10] = color.y; _triVertices[11] = color.z;
		_triVertices[15] = color.x; _triVertices[16] = color.y; _triVertices[17] = color.z;
	}
	else if (_type == Engine::ShapeType::Quad) {
		_quadVertices[3] = color.x;  _quadVertices[4] = color.y;  _quadVertices[5] = color.z;
		_quadVertices[9] = color.x;  _quadVertices[10] = color.y; _quadVertices[11] = color.z;
		_quadVertices[15] = color.x; _quadVertices[16] = color.y; _quadVertices[17] = color.z;
		_quadVertices[21] = color.x; _quadVertices[22] = color.y; _quadVertices[23] = color.z;
	}
}

void Shape::SetColor(float r, float g, float b) {
	if (_type == Engine::ShapeType::Triangle) {
		_triVertices[3] = r;  _triVertices[4] = g;  _triVertices[5] = b;
		_triVertices[9] = r; _triVertices[10] = g; _triVertices[11] = b;
		_triVertices[15] = r; _triVertices[16] = g; _triVertices[17] = b;
	}
	else if (_type == Engine::ShapeType::Quad) {
		_quadVertices[3] = r;  _quadVertices[4] = g;  _quadVertices[5] = b;
		_quadVertices[9] = r; _quadVertices[10] = g; _quadVertices[11] = b;
		_quadVertices[15] = r; _quadVertices[16] = g; _quadVertices[17] = b;
		_quadVertices[21] = r; _quadVertices[22] = g; _quadVertices[23] = b;
	}
}

void Shape::Draw() {
	if(_type == Engine::ShapeType::Triangle)
		_renderer->Draw(_shader, _vao, _vbo, _triVertices, 18, _triIndices, 3, 6);
	else if (_type == Engine::ShapeType::Quad)
		_renderer->Draw(_shader, _vao, _vbo, _quadVertices, 24, _quadIndices, 6, 6);
}