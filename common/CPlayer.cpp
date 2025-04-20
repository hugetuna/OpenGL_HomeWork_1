#include "CPlayer.h"

//建構時必須記憶使用的shader
CPlayer::CPlayer(GLuint shaderID) {
	shape.setupVertexAttributesAtOnce();
	shape.setShaderIDAtOnce(shaderID);
	_shaderID = shaderID;
	shape.updateAtOnce(glm::vec3(0, 0, 0), 0);
	position = glm::vec3(0, 0, 0);
	radius = 0.6;
}
CPlayer::~CPlayer() {
}
void CPlayer::shoot() {
	glm::vec3 bulletDir(0, 1, 0); // 固定向上
	CBullet* bullet = new CBullet(getPos(), bulletDir, 4.0f, _shaderID);
	_bullets.add(bullet);
}
void CPlayer::update(float dt) {
	shape.updateAtOnce(position, dt);
	// 更新子彈
	_bullets.update(dt);
}
void CPlayer::setPos(glm::vec3 destination) {
	position = destination;
}
void CPlayer::render() {
	shape.drawAtOnce();
	// 畫出所有子彈
	_bullets.draw();
}