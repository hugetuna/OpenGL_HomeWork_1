#include <cmath>

#include "CPlayerShape.h"
#include "CShape.h"
#include "initshader.h"

#define PI 3.14159265358979f

//由三個形狀組成的主角
CPlayerShape::CPlayerShape() {
    // 建立三種帽子
    _hatList.push_back(new CTriangle());
    _hatList.push_back(new CStar());
    _hatList.push_back(new CTrapezoid());
    _head = new CCircle(36);          //頭
    _cloak = new CTrapezoid();       // 斗篷
    shieldCount = 3;
    shieldAngle = 0;
    _shields = new CHex[shieldCount];

    for (auto hat : _hatList) {
        hat->setPos(glm::vec3(0.0f, 0.3f, 0.0f));
        hat->setScale(glm::vec3(0.5f, 0.5f, 0.0f));
    } 
    //幫星星改個顏色
    _hatList[1]->setColor(glm::vec3(0.3f, 0.8f, 0.8f));
    _head->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    _head->setScale(glm::vec3(0.5f, 0.5f, 0.0f));
    _cloak->setPos(glm::vec3(0.0f, -0.5f, 0.0f));
    _cloak->setScale(glm::vec3(0.6f, 0.6f, 0.0f));
    for (int i = 0; i < shieldCount; i++)
    {
        float angle = 2.0f * PI * i / shieldCount;
        float x = cos(angle) * 0.8f;
        float y = sin(angle) * 0.8f;
        _shields[i].setPos(glm::vec3(x, y, 0.0f));
    }
}

CPlayerShape::~CPlayerShape() {
    for (auto hat : _hatList) {
        delete hat;
    }
    delete _head;
    delete _cloak;
    delete[] _shields;
}
void CPlayerShape::setupVertexAttributesAtOnce() {
    for (auto hat : _hatList) {
        hat->setupVertexAttributes();
    }
    _head->setupVertexAttributes();
    _cloak->setupVertexAttributes();
    for (int i = 0; i < shieldCount; i++)
    {
        _shields[i].setupVertexAttributes();
    }
}
void CPlayerShape::setShaderIDAtOnce(GLuint shaderID) {
    for (auto hat : _hatList) {
        hat->setShaderID(shaderID);
    }
    _head->setShaderID(shaderID);
    _cloak->setShaderID(shaderID);
    for (int i = 0; i < shieldCount; i++)
    {
        _shields[i].setShaderID(shaderID);
    }
}

void CPlayerShape::updateAtOnce(glm::vec3 pos,float dt) {
    // 可加偏移調整組合位移
    for (auto hat : _hatList) {
        hat->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    }
    _head->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _cloak->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    //旋轉盾
    shieldAngle += dt*180;
    if (shieldAngle>=360.0f)
    {
        shieldAngle -= 360.0f;
    }
    for (int i = 0; i < shieldCount; i++)
    {
        float angle = 2.0f * PI * i / shieldCount;
        float x = cos(angle) * 0.8f;
        float y = sin(angle) * 0.8f;
        _shields[i].setPos(glm::vec3(x, y, 0.0f));
    }
    for (int i = 0; i < shieldCount; i++)
    {
        float shieldRadians = glm::radians(shieldAngle);
        glm::mat4 rotateMX=glm::rotate(glm::mat4(1.0f), shieldRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 transformMX = glm::translate(glm::mat4(1.0f), pos);
        _shields[i].setTransformMatrix(transformMX*rotateMX);
    }
}
void CPlayerShape::drawAtOnce() {
    _head->draw();
    //三個都生成，但只畫正確的編號
    if (_hatOnHead >= 0 && _hatOnHead < _hatList.size())
        _hatList[_hatOnHead]->draw();
    _cloak->draw();
    for (int i = 0; i < shieldCount; i++)
    {
        _shields[i].draw();
    }
}
void CPlayerShape::changeHat() {
    _hatOnHead = (_hatOnHead + 1) % _hatList.size();
}
//盾牌增減邏輯
void CPlayerShape::removeOneShield() {
    if (shieldCount > 0) {
        shieldCount--;
    }
}

int CPlayerShape::getShieldCount() {
    return shieldCount;
}
