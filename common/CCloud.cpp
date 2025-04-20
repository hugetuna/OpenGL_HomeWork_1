// CCloud.cpp
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CCloud.h"

CCloud::CCloud(glm::vec3 pos, float speed, GLuint shaderID)
    : _position(pos), _speed(speed) {
    _cloudShape = new CCircle(32);
    _cloudShape->setupVertexAttributes();
    _cloudShape->setShaderID(shaderID);
    _cloudShape->setColor(glm::vec3(0.9f, 0.9f, 1.0f));  // ²HÂÅ¥Õ¦â
    _cloudShape->setScale(glm::vec3(0.8f, 0.4f, 0.0f));  // ¾ò¶ê¶³¦·
    _cloudShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
}

void CCloud::update(float deltaTime) {
    _position.y -= _speed * deltaTime;
    _cloudShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
}

void CCloud::draw() {
    _cloudShape->draw();
}
