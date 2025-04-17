#include <cmath>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CBullet.h"
#include "initshader.h"


CBullet::CBullet(const glm::vec3& position, const glm::vec3& direction, float speed, GLuint shaderID)
    : _position(position), _velocity(glm::normalize(direction)), _speed(speed) {
    _active = true;
    _bulletShape = new CCircle(32); // 預設圓形子彈
    _bulletShape->setupVertexAttributes();
    _bulletShape->setShaderID(shaderID);
    _bulletShape->setColor(glm::vec3(1.0f, 0.4f, 0.7f));
    _bulletShape->setScale(glm::vec3(0.3f, 0.3f, 0));
    _bulletShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
}

CBullet::~CBullet() {
    delete _bulletShape;
}

void CBullet::update(float deltaTime) {
    _position += _velocity * _speed * deltaTime;
    _bulletShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
}

void CBullet::draw() {
    if (_active) {
        _bulletShape->draw();
    }
}

glm::vec3 CBullet::getPosition() const { return _position; }
bool CBullet::isActive() const { return _active; }
void CBullet::deactivate() { _active = false; }
