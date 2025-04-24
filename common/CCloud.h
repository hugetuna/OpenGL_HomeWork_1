// CCloud.h
#pragma once
#include <cmath>
#include <vector>
#include <glew/include/GL/glew.h>
#include "CCircle.h"

class CCloud {
private:
    std::vector<CCircle*> _parts;
    glm::vec3 _position;
    float _dropAmount;//為了正確模擬，額外宣告雲的下降量
    float _speed;

public:
    CCloud(glm::vec3 position, float speed, GLuint shaderID);
    ~CCloud();

    void update(float deltaTime);
    void draw();
    glm::vec3 getPosition() const;
};

