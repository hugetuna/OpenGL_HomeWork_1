#include "CEnemy_Bat.h"

//�غc�ɥ����O�ШϥΪ�shader
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
	// �ھڭ����V����
	if (_flyDirection)
		_position += glm::vec3(0, -_flySpeed * dt, 0);
	else
		_position += glm::vec3(0, _flySpeed * dt, 0);

	// ��F�W�U��ɮɧ��ܤ�V
	if (_position.y >= 3.5f || _position.y <= -3.5f)
		_flyDirection = !_flyDirection;

	_pShape->updateAtOnce(_position, dt);
	_attackTimer += dt;
}

std::vector<CEnemyBullet*> CEnemy_Bat::shoot(glm::vec3 targetPos) {
	// ��V�n�O�o�������V�q
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::vector<CEnemyBullet*> bullets;

	bullets.push_back(new CEnemyBullet(_position, dir, 2.0f, _shaderID));

	return bullets;
}

