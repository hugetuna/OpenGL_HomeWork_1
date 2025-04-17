// CBullet.h
#pragma once
#include <glm/glm.hpp>
#include "CCircle.h"

class CBullet {
private:
    CCircle* _bulletShape;// ¹Ï§Î (has-a)
    glm::vec3 _position;
    glm::vec3 _velocity;
    float _speed;
    bool _active = true;

public:
    CBullet(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& direction = glm::vec3(0, 1, 0), float speed = 1.5f, GLuint shaderID=0);
    ~CBullet();

    void update(float deltaTime);

    void draw();

    glm::vec3  getPosition()const;
    bool isActive()const;
    void deactivate();
};