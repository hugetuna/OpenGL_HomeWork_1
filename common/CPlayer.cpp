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
	for (auto b : _bullets) delete b;
}
void CPlayer::shoot() {
	glm::vec3 bulletDir(0, 1, 0); // 固定向上
	CBullet* bullet = new CBullet(getPos(), bulletDir, 4.0f, _shaderID);
	_bullets.push_back(bullet);
}
void CPlayer::update(float dt) {
	shape.updateAtOnce(position, dt);
	// 更新子彈
	for (auto bullet : _bullets) {
		bullet->update(dt);
	}
}
void CPlayer::setPos(glm::vec3 destination) {
	position = destination;
}
void CPlayer::render() {
	shape.drawAtOnce();
	// 畫出所有子彈
	for (auto bullet : _bullets) {
		bullet->draw();
	}
}