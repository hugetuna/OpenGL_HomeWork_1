#include "CEnemyShape_Slime.h"

CEnemyShape_Slime::CEnemyShape_Slime(GLuint shaderID)
    : CEnemyShape(shaderID)
{
    _pBody = new CCircle(36);
    _pEyeL = new CCircle(36);
    _pEyeR = new CCircle(36);
    _pMouth = new CTrapezoid();

    // 主體
    _pBody->setPos(glm::vec3(0.0f, -0.2f, 0.0f));
    _pBody->setColor(glm::vec3(0.2f, 0.8f, 0.3f));
    _pBody->setScale(glm::vec3(0.7f, 0.5f, 1.0f));

    // 左眼
    _pEyeL->setPos(glm::vec3(-0.2f, 0.0f, 0.0f));
    _pEyeL->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    _pEyeL->setScale(glm::vec3(0.08f, 0.08f, 1.0f));

    // 右眼
    _pEyeR->setPos(glm::vec3(0.2f, 0.0f, 0.0f));
    _pEyeR->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    _pEyeR->setScale(glm::vec3(0.08f, 0.08f, 1.0f));

    // 嘴巴
    _pMouth->setPos(glm::vec3(0.0f, -0.15f, 0.0f));
    _pMouth->setColor(glm::vec3(0.1f, 0.1f, 0.1f));
    _pMouth->setScale(glm::vec3(0.2f, 0.1f, 1.0f));
    _pMouth->setRotZ(0.0f);
}

CEnemyShape_Slime::~CEnemyShape_Slime() {
    delete _pBody;
    delete _pEyeL;
    delete _pEyeR;
    delete _pMouth;
}

void CEnemyShape_Slime::setupVertexAttributesAtOnce() {
    _pBody->setupVertexAttributes();
    _pEyeL->setupVertexAttributes();
    _pEyeR->setupVertexAttributes();
    _pMouth->setupVertexAttributes();
}

void CEnemyShape_Slime::setShaderIDAtOnce() {
    _pBody->setShaderID(_shaderID);
    _pEyeL->setShaderID(_shaderID);
    _pEyeR->setShaderID(_shaderID);
    _pMouth->setShaderID(_shaderID);
}

void CEnemyShape_Slime::updateAtOnce(glm::vec3 pos, float dt) {
    _pBody->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pEyeL->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pEyeR->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pMouth->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
}

void CEnemyShape_Slime::drawAtOnce() {
    _pBody->draw();
    _pEyeL->draw();
    _pEyeR->draw();
    _pMouth->draw();
}
