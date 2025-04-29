#include "CPlayer.h"

//建構時必須記憶使用的shader
CPlayer::CPlayer(GLuint shaderID) {
	shape.setupVertexAttributesAtOnce();
	shape.setShaderIDAtOnce(shaderID);
	_shaderID = shaderID;
	shape.updateAtOnce(glm::vec3(0, 0, 0), 0);
	position = glm::vec3(0, 0, 0);
	radius = 0.6;
	flashTimer = 0;
}
CPlayer::~CPlayer() {
}
void CPlayer::shoot() {
	glm::vec3 bulletDir(0, 1, 0); // 固定向上
	CBullet* bullet = new CBullet(getPos(), bulletDir, 4.0f, _shaderID);
	_bullets.add(bullet);
}
void CPlayer::update(float dt, CEnemyBulletList& enemyBullets) {
	shape.updateAtOnce(position, dt);
	//判定是否被擊中
	// 被子彈打到
	for (EnemyBulletNode* current = enemyBullets.getHead(); current != nullptr; current = current->next) {
		if (current->bullet->isActive()) {
			float dist = glm::length(this->getPos()- current->bullet->getPosition());
			if (dist < this->getRadius()) {
				current->bullet->deactivate();
				shape.removeOneShield();
				flashTimer = 0.5f;
			}
		}
	}
	// 每幀減少計時
	if (flashTimer > 0.0f) {
		flashTimer -= dt;
	}
	// 更新自己的子彈
	_bullets.update(dt);
}
void CPlayer::setPos(glm::vec3 destination) {
	position = destination;
}
void CPlayer::render() {
	glUseProgram(_shaderID);
	GLint flashLoc = glGetUniformLocation(_shaderID, "u_Flash");
	glUniform1i(flashLoc, flashTimer > 0.0f ? 1 : 0);
	shape.drawAtOnce();
	// 畫出所有子彈
	_bullets.draw();
}