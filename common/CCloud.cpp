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
    // 雲的基本樣式：三～五個圓，位置有點高低不同
    int numCircles = 3 + rand() % 3;  // 3~5 個圓
    for (int i = 0; i < numCircles; ++i) {
        CCircle* circle = new CCircle(32);
        circle->setupVertexAttributes();
        circle->setShaderID(shaderID);
        circle->setColor(glm::vec3(0.9f, 1.0f, 0.9f));  // 純白或略帶淡灰
        circle->setScale(glm::vec3(0.6f + rand() % 10 * 0.05f));  // 稍微不同大小

        // 雲朵裡的圓會在 x 軸稍微偏移，y 軸可微小上下浮動
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
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, _dropAmount,0));  // 平移到新位置
        circle->setTransformMatrix(trans);  // 重設位置
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

