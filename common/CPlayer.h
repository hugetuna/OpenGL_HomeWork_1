#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "CPlayerShape.h"
#include "CBullet.h"
#include "CBulletList.h"
#include "CEnemyBulletList.h"

class CPlayer {
public:

    CPlayer(GLuint shaderID);
    ~CPlayer();
    void update(float dt,CEnemyBulletList& enemyBullets);

    void render();
    void setPos(glm::vec3 destination);
    void shoot(); // 射擊功能
    glm::vec3 getPos() { return position; }
    float getRadius() { return radius; }
    CBulletList& getBulletList() { return _bullets; }
private:
    CBulletList _bullets;
    CPlayerShape shape;
    glm::vec3 position;
    GLuint _shaderID;
    float radius; // 頭跟斗篷差不多這麼大
    float flashTimer;
};
