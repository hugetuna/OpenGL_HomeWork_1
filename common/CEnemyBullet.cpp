#include "CEnemyBullet.h"
#include <glm/gtc/matrix_transform.hpp>

CEnemyBullet::CEnemyBullet(const glm::vec3& position, const glm::vec3& direction, float speed, GLuint shaderID)
    : _position(position), _velocity(glm::normalize(direction)), _speed(speed), _active(true)
{
    _bulletShape = new CCircle(16); // �ĤH�l�u�A�y�L²���I
    _bulletShape->setupVertexAttributes();
    _bulletShape->setShaderID(shaderID);
    _bulletShape->setColor(glm::vec3(0.4f, 0.8f, 1.0f)); // �H�Ŧ�
    _bulletShape->setScale(glm::vec3(0.25f, 0.25f, 0));
    _bulletShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
}

CEnemyBullet::~CEnemyBullet() {
    delete _bulletShape;
}

void CEnemyBullet::update(float deltaTime) {
    _position += _velocity * _speed * deltaTime;
    _bulletShape->setTransformMatrix(glm::translate(glm::mat4(1.0f), _position));
    // �W�X�e����ɮɦ۰ʮ���
    if (_position.x < -3.5f || _position.x > 3.5f ||
        _position.y < -4.5f || _position.y > 4.5f) {
        deactivate();
    }
}

void CEnemyBullet::draw() {
    if (_active) {
        _bulletShape->draw();
    }
}

void CEnemyBullet::deactivate() {
    _active = false;
}

glm::vec3 CEnemyBullet::getPosition() const {
    return _position;
}

bool CEnemyBullet::isActive() const {
    return _active;
}

