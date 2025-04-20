// CCloud.h
#pragma once
#include <cmath>
#include <glew/include/GL/glew.h>
#include "CCircle.h"

class CCloud {
public:
    CCloud(glm::vec3 pos, float speed, GLuint shaderID);
    void update(float deltaTime);
    void draw();
    glm::vec3 getPosition() const { return _position; };
private:
    glm::vec3 _position;
    float _speed;
    CCircle* _cloudShape;
};
