#pragma once

#include <glm/glm.hpp>
#include <glew/include/GL/glew.h>
#include "CCircle.h"

class CEnemyBullet {
public:
    CEnemyBullet(const glm::vec3& position, const glm::vec3& direction, float speed, GLuint shaderID);
    ~CEnemyBullet();

    void update(float deltaTime);
    void draw();
    void deactivate();

    glm::vec3 getPosition() const;
    bool isActive() const;

private:
    //�_�l�I�B��V�B�t�סB�O�_�Ұ�
    glm::vec3 _position;
    glm::vec3 _velocity;
    float _speed;
    bool _active;
    CCircle* _bulletShape;
};
