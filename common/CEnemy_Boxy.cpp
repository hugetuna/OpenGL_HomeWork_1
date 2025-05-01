#include "CEnemy_Boxy.h"

//�غc�ɥ����O�ШϥΪ�shader
CEnemy_Boxy::CEnemy_Boxy(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Boxy(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
	_hp = 5;
	_attackInterval = 4;
	_attackTimer = 2;

	_moveTime = 0.0f;
	_position = glm::vec3(0, 2.5f, 0); // �T�w����
}
CEnemy_Boxy::~CEnemy_Boxy() {
	
}
void CEnemy_Boxy::update(float dt, glm::vec3 playerPos) {
	_moveTime += dt;

	// �ϥ� Lissajous ���u 8 �r�β��� (�i�վ㮶�T�P�W�v)
	float x = 3.0f * sin(_moveTime);
	float y = 2.5f+1.5f * sin(_moveTime) * cos(_moveTime);
	_position.x = x;
	_position.y = y;
	// y �T�w����

	_pShape->updateAtOnce(_position, dt);
	_attackTimer += dt;
}
std::vector<CEnemyBullet*> CEnemy_Boxy::shoot(glm::vec3 targetPos) {
	// ��V�n�O�o�������V�q
	std::vector<CEnemyBullet*> bullets;

	// �T�өT�w��V�A���U�o�g
	glm::vec3 down = glm::normalize(glm::vec3(0, -1, 0));
	glm::vec3 leftDown = glm::normalize(glm::vec3(-0.5f, -1, 0));
	glm::vec3 rightDown = glm::normalize(glm::vec3(0.5f, -1, 0));

	bullets.push_back(new CEnemyBullet(_position, down, 1.2f, _shaderID));
	bullets.push_back(new CEnemyBullet(_position, leftDown, 1.2f, _shaderID));
	bullets.push_back(new CEnemyBullet(_position, rightDown, 1.2f, _shaderID));

	return bullets;
}
