#include "CEnemy_Boxy.h"

//建構時必須記憶使用的shader
CEnemy_Boxy::CEnemy_Boxy(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Boxy(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
}
CEnemy_Boxy::~CEnemy_Boxy() {
	
}
CEnemyBullet* CEnemy_Boxy::shoot(glm::vec3 targetPos) {
	// 方向要記得做成單位向量
	glm::vec3 dir = glm::normalize(targetPos - _position);
	std::cout << "敵人發射子彈\n";
	return new CEnemyBullet(_position, dir, 1.0f, _shaderID);
}
