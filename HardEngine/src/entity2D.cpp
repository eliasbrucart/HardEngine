#include "entity2D.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

Entity2D::Entity2D() {
	model.translate = glm::mat4(1.0f);
	model.rotation.x = glm::mat4(1.0f);
	model.rotation.y = glm::mat4(1.0f);
	model.rotation.z = glm::mat4(1.0f);
	model.scale = glm::mat4(1.0f);
	Translate(1.0f, 1.0f, 1.0f);
	RotateX(0.0f);
	RotateY(0.0f);
	RotateZ(0.0f);
	Scale(1.0f, 1.0f, 1.0f);
}

Entity2D::~Entity2D() {

}

void Entity2D::UpdateModel() {
	model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
}

void Entity2D::UpdateMatrices() {

}

void Entity2D::Translate(float x, float y, float z) {
	model.translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	UpdateModel();
}

void Entity2D::RotateX(float angle) {
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;
	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	UpdateModel();
}

void Entity2D::RotateY(float angle) {
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;
	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	UpdateModel();
}

void Entity2D::RotateZ(float angle) {
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;
	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	UpdateModel();
}

void Entity2D::Scale(float x, float y, float z) {
	model.scale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
	UpdateModel();
}

glm::mat4 Entity2D::GetModel() {
	return model.trs;
}