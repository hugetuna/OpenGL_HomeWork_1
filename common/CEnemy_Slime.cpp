#include "CEnemy_Slime.h"

//�غc�ɥ����O�ШϥΪ�shader
CEnemy_Slime::CEnemy_Slime(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Slime(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
}
CEnemy_Slime::~CEnemy_Slime() {
	
}
CEnemyBullet* CEnemy_Slime::shoot(glm::vec3 targetPos) {
	// ��V�n�O�o�������V�q
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::cout << "�ĤH�o�g�l�u\n";
	return new CEnemyBullet(_position, dir, 1.0f, _shaderID);
}
