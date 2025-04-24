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
    //todo:�~�ӫ��@�Ϊ�
    glm::vec3 position;
    GLuint _shaderID;
    float radius; // �Y����O�t���h�o��j
};
