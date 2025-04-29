#include "CEnemy_Bat.h"

//�غc�ɥ����O�ШϥΪ�shader
CEnemy_Bat::CEnemy_Bat(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Bat(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
	
}
CEnemy_Bat::~CEnemy_Bat() {
	
}
CEnemyBullet* CEnemy_Bat::shoot(glm::vec3 targetPos) {
	// ��V�n�O�o�������V�q
	glm::vec3 dir = glm::normalize(targetPos - _position);
	//std::cout << "�ĤH�o�g�l�u\n";
	return new CEnemyBullet(_position, dir, 1.0f, _shaderID);
}

