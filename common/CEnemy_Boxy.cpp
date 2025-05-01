#include "CEnemy_Boxy.h"

//建構時必須記憶使用的shader
CEnemy_Boxy::CEnemy_Boxy(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Boxy(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
	_hp = 5;
	_attackInterval = 4;
	_attackTimer = 2;

	_moveTime = 0.0f;
	_position = glm::vec3(0, 2.5f, 0); // 固定高度
}
CEnemy_Boxy::~CEnemy_Boxy() {
	
}
void CEnemy_Boxy::update(float dt, glm::vec3 playerPos) {
	_moveTime += dt;

	// 使用 Lissajous 曲線 8 字形移動 (可調整振幅與頻率)
	float x = 3.0f * sin(_moveTime);
	float y = 2.5f+1.5f * sin(_moveTime) * cos(_moveTime);
	_position.x = x;
	_position.y = y;
	// y 固定不動

	_pShape->updateAtOnce(_position, dt);
	_attackTimer += dt;
}
std::vector<CEnemyBullet*> CEnemy_Boxy::shoot(glm::vec3 targetPos) {
	// 方向要記得做成單位向量
	std::vector<CEnemyBullet*> bullets;

	// 三個固定方向，往下發射
	glm::vec3 down = glm::normalize(glm::vec3(0, -1, 0));
	glm::vec3 leftDown = glm::normalize(glm::vec3(-0.5f, -1, 0));
	glm::vec3 rightDown = glm::normalize(glm::vec3(0.5f, -1, 0));

	bullets.push_back(new CEnemyBullet(_position, down, 1.2f, _shaderID));
	bullets.push_back(new CEnemyBullet(_position, leftDown, 1.2f, _shaderID));
	bullets.push_back(new CEnemyBullet(_position, rightDown, 1.2f, _shaderID));

	return bullets;
}
