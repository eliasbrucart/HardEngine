#include "Game.h"
#include "vec3.hpp"

Game::Game(){
	_shape = new Engine::Shape(shaders, ShapeType::Quad);
}

Game::~Game() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}

void Game::InitGame() {
	_shape->SetColor(1.0f, 0.0f, 0.0f);
	_shape->InitShape();
}

void Game::UpdateGame() {
	_shape->Draw();
}

void Game::UnloadGame() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}