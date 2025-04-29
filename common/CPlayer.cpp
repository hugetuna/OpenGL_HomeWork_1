#include "CPlayer.h"

//�غc�ɥ����O�ШϥΪ�shader
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
	glm::vec3 bulletDir(0, 1, 0); // �T�w�V�W
	CBullet* bullet = new CBullet(getPos(), bulletDir, 4.0f, _shaderID);
	_bullets.add(bullet);
}
void CPlayer::update(float dt, CEnemyBulletList& enemyBullets) {
	shape.updateAtOnce(position, dt);
	//�P�w�O�_�Q����
	// �Q�l�u����
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
	// �C�V��֭p��
	if (flashTimer > 0.0f) {
		flashTimer -= dt;
	}
	// ��s�ۤv���l�u
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
	// �e�X�Ҧ��l�u
	_bullets.draw();
}