#include "CEnemy.h"

//建構時必須記憶使用的shader
CEnemy::CEnemy(GLuint shaderID) {
	_shaderID = shaderID;
	position = glm::vec3(0, 0, 0);
	radius = 0.6;
}
CEnemy::~CEnemy() {
}
void CEnemy::update(float dt) {
	
}
void CEnemy::render() {
	
}
void CEnemy::setPos(glm::vec3 destination) {
	position = destination;
}