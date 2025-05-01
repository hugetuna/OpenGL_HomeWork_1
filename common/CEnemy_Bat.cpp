#include "CEnemy_Bat.h"

//建構時必須記憶使用的shader
CEnemy_Bat::CEnemy_Bat(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Bat(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
	_hp = 6;
	_attackInterval = 2;
	_attackTimer = 1;
	_flyDirection = true;
	_flySpeed = 1.5f;
}
CEnemy_Bat::~CEnemy_Bat() {
	
}
void CEnemy_Bat::update(float dt, glm::vec3 playerPos) {
	// 根據飛行方向移動
	if (_flyDirection)
		_position += glm::vec3(0, -_flySpeed * dt, 0);
	else
		_position += glm::vec3(0, _flySpeed * dt, 0);

	// 到達上下邊界時改變方向
	if (_position.y >= 3.5f || _position.y <= -3.5f)
		_flyDirection = !_flyDirection;

	_pShape->updateAtOnce(_position, dt);
	_attackTimer += dt;
}

std::vector<CEnemyBullet*> CEnemy_Bat::shoot(glm::vec3 targetPos) {
	// 方向要記得做成單位向量
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::vector<CEnemyBullet*> bullets;

	bullets.push_back(new CEnemyBullet(_position, dir, 2.0f, _shaderID));

	return bullets;
}

