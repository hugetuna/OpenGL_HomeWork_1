#include "CEnemy_Slime.h"

//建構時必須記憶使用的shader
CEnemy_Slime::CEnemy_Slime(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Slime(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
}
CEnemy_Slime::~CEnemy_Slime() {
	
}
CEnemyBullet* CEnemy_Slime::shoot(glm::vec3 targetPos) {
	// 方向要記得做成單位向量
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::cout << "敵人發射子彈\n";
	return new CEnemyBullet(_position, dir, 1.0f, _shaderID);
}
