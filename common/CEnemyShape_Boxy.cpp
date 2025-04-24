#include "CEnemyShape_Boxy.h"

CEnemyShape_Boxy::CEnemyShape_Boxy(GLuint shaderID)
    : CEnemyShape(shaderID)
{
    _pBody = new CQuad();
    _pEyeL = new CCircle(24);
    _pEyeR = new CCircle(24);
    _pDecoration = new CStar(4);

    // 主體：藍紫方塊
    _pBody->setPos(glm::vec3(0.0f, -0.05f, 0.0f));
    _pBody->setColor(glm::vec3(0.6f, 0.7f, 1.0f));
    _pBody->setScale(glm::vec3(0.5f, 0.5f, 1.0f));

    // 左眼：黑色小圓
    _pEyeL->setPos(glm::vec3(-0.15f, 0, 0.01f));
    _pEyeL->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    _pEyeL->setScale(glm::vec3(0.07f, 0.07f, 1.0f));

    // 右眼
    _pEyeR->setPos(glm::vec3(0.15f, 0, 0.01f));
    _pEyeR->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    _pEyeR->setScale(glm::vec3(0.07f, 0.07f, 1.0f));
    //頭部飾品
    _pDecoration->setPos(glm::vec3(0.0f, 0.2f, 0.01f));
    _pDecoration->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    _pDecoration->setScale(glm::vec3(0.4f, 0.4f, 1.0f));
}

CEnemyShape_Boxy::~CEnemyShape_Boxy() {
    delete _pBody;
    delete _pEyeL;
    delete _pEyeR;
    delete _pDecoration;
}

void CEnemyShape_Boxy::setupVertexAttributesAtOnce() {
    _pBody->setupVertexAttributes();
    _pEyeL->setupVertexAttributes();
    _pEyeR->setupVertexAttributes();
    _pDecoration->setupVertexAttributes();
}

void CEnemyShape_Boxy::setShaderIDAtOnce() {
    _pBody->setShaderID(_shaderID);
    _pEyeL->setShaderID(_shaderID);
    _pEyeR->setShaderID(_shaderID);
    _pDecoration->setShaderID(_shaderID);
}

void CEnemyShape_Boxy::updateAtOnce(glm::vec3 pos, float dt) {
    _pBody->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pEyeL->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pEyeR->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _pDecoration->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
}

void CEnemyShape_Boxy::drawAtOnce() {
    _pBody->draw();
    _pEyeL->draw();
    _pEyeR->draw();
    _pDecoration->draw();
}

