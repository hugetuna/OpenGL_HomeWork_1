#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include "CEnemyShape.h"
#include "CEnemyBullet.h"
#include "CEnemyBulletList.h"

class CEnemy {
public:

    CEnemy(GLuint shaderID);
    virtual ~CEnemy();
    virtual void update(float dt);
    virtual void render();

    void setPos(glm::vec3 destination);
    glm::vec3 getPos() { return _position; }
    float getRadius() { return _radius; }
    //發射子彈
    virtual CEnemyBullet* shoot(glm::vec3 targetPos) { return nullptr; }
    bool readyToShoot();
    //受傷邏輯
    void takeDamage(int dmg);
    bool isDead();
protected:
    CEnemyShape* _pShape;
    glm::vec3 _position;
    GLuint _shaderID;
    float _radius;
    int _hp; // ★血量
    //攻擊頻率與計時器
    float _attackTimer;
    float _attackInterval;
};
