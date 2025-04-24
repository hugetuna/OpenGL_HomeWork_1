#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class CEnemy {
public:

    CEnemy(GLuint shaderID);
    ~CEnemy();
    virtual void update(float dt);
    virtual void render();

    void setPos(glm::vec3 destination);
    glm::vec3 getPos() { return position; }
    float getRadius() { return radius; }
private:
    //todo:繼承後實作形狀
    glm::vec3 position;
    GLuint _shaderID;
    float radius; // 頭跟斗篷差不多這麼大
};
