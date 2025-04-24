// CCloud.cpp
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include "CCloud.h"


CCloud::CCloud(glm::vec3 position, float speed, GLuint shaderID)
    : _position(position), _speed(speed)
{
    _dropAmount = 0;
    // �����򥻼˦��G�T�㤭�Ӷ�A��m���I���C���P
    int numCircles = 3 + rand() % 3;  // 3~5 �Ӷ�
    for (int i = 0; i < numCircles; ++i) {
        CCircle* circle = new CCircle(32);
        circle->setupVertexAttributes();
        circle->setShaderID(shaderID);
        circle->setColor(glm::vec3(0.9f, 1.0f, 0.9f));  // �¥թβ��a�H��
        circle->setScale(glm::vec3(0.6f + rand() % 10 * 0.05f));  // �y�L���P�j�p

        // �����̪���|�b x �b�y�L�����Ay �b�i�L�p�W�U�B��
        float xOffset = (float)(i - numCircles / 2) * 0.3f + ((rand() % 20) - 10) * 0.01f;
        float yOffset = ((rand() % 20) - 10) * 0.01f;
        glm::vec3 offset = _position + glm::vec3(xOffset, yOffset, 0.0f);
        circle->setPos(offset);

        _parts.push_back(circle);
    }
}

CCloud::~CCloud() {
    for (auto part : _parts)
        delete part;
    _parts.clear();
}

void CCloud::update(float deltaTime) {
    _position.y -= _speed * deltaTime;
    _dropAmount -= _speed * deltaTime;
    for (auto circle : _parts) {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, _dropAmount,0));  // ������s��m
        circle->setTransformMatrix(trans);  // ���]��m
    }
}

void CCloud::draw() {
    for (auto circle : _parts) {
        circle->draw();
    }
}

glm::vec3 CCloud::getPosition() const {
    return _position;
}

