#include "CEnemy.h"

//建構時必須記憶使用的shader
CEnemy::CEnemy(GLuint shaderID) {
	_shaderID = shaderID;
	_position = glm::vec3(0, 0, 0);
	_radius = 0.6;
	_hp = 3;
	_attackTimer = 0;
	_attackInterval = 2.0f;
}
CEnemy::~CEnemy() {
	if (_pShape) {
		delete _pShape;
		_pShape = nullptr;
	}
}
void CEnemy::update(float dt, glm::vec3 playerPos) {
	_pShape->updateAtOnce(_position,dt);
	_attackTimer += dt;
}
void CEnemy::render() {
	_pShape->drawAtOnce();
}
void CEnemy::setPos(glm::vec3 destination) {
	_position = destination;
}
//射擊計算機
bool CEnemy::readyToShoot() {
	if (_attackTimer>= _attackInterval)
	{
		_attackTimer = 0;
		return true;
	}
	else
	{
		return false;
	}
}
//受傷邏輯
void CEnemy::takeDamage(int dmg) {
	_hp -= dmg;
	if (_hp < 0) _hp = 0;
}

bool CEnemy::isDead() {
	return _hp <= 0;
}