#include "CEnemyShape_Bat.h"

//建構時必須記憶使用的shader
CEnemyShape_Bat::CEnemyShape_Bat(GLuint shaderID) : CEnemyShape(shaderID) {
	_pHead = new CCircle(36);
	_pEye = new CCircle(36);
	_pWingLeft = new CTriangle();
	_pWingRight = new CTriangle();
	//基礎設定
	//頭
	_pHead->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	_pHead->setColor(glm::vec3(0.4f, 0.0f, 0.8f));
	_pHead->setScale(glm::vec3(0.55f, 0.55f, 1.0f));
	//眼
	_pEye->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	_pEye->setColor(glm::vec3(0.9f, 0.0f, 0.3f));
	_pEye->setScale(glm::vec3(0.4f, 0.2f, 1.0f));
	//左翼
	_pWingLeft->setPos(glm::vec3(-0.4f, 0.1f, 0.0f));
	_pWingLeft->setColor(glm::vec3(0.4f, 0.0f, 0.8f));
	_pWingLeft->setScale(glm::vec3(0.4f, 0.3f, 1.0f));
	_pWingLeft->setRotZ(150.0f);
	//右翼
	_pWingRight->setPos(glm::vec3(0.4f, 0.1f, 0.0f));
	_pWingRight->setColor(glm::vec3(0.4f, 0.0f, 0.8f));
	_pWingRight->setScale(glm::vec3(0.4f, 0.3f, 1.0f));
	_pWingRight->setRotZ(-150.0f);
}
CEnemyShape_Bat::~CEnemyShape_Bat() {
	delete _pHead;
	delete _pEye;
	delete _pWingLeft;
	delete _pWingRight;
}

void CEnemyShape_Bat::setupVertexAttributesAtOnce() {
	_pHead->setupVertexAttributes();
	_pEye->setupVertexAttributes();
	_pWingLeft->setupVertexAttributes();
	_pWingRight->setupVertexAttributes();
}

void CEnemyShape_Bat::setShaderIDAtOnce() {
	_pHead->setShaderID(_shaderID);
	_pEye->setShaderID(_shaderID);
	_pWingLeft->setShaderID(_shaderID);
	_pWingRight->setShaderID(_shaderID);
}

void CEnemyShape_Bat::updateAtOnce(glm::vec3 pos, float dt) {
	_pHead->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
	_pEye->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
	_pWingLeft->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
	_pWingRight->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
}
void CEnemyShape_Bat::drawAtOnce() {
	_pHead->draw();
	_pEye->draw();
	_pWingLeft->draw();
	_pWingRight->draw();
}