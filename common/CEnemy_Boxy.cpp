#include "CEnemy_Boxy.h"

//�غc�ɥ����O�ШϥΪ�shader
CEnemy_Boxy::CEnemy_Boxy(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Boxy(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
}
CEnemy_Boxy::~CEnemy_Boxy() {
	
}
CEnemyBullet* CEnemy_Boxy::shoot(glm::vec3 targetPos) {
	// ��V�n�O�o�������V�q
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::cout << "�ĤH�o�g�l�u\n";
	return new CEnemyBullet(_position, dir, 1.0f, _shaderID);
}
