#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CEnemy.h"
#include "CEnemyShape_Bat.h"

class CEnemy_Bat:public CEnemy {
public:
    CEnemy_Bat(GLuint shaderID);
    ~CEnemy_Bat();
    virtual void update(float dt,glm::vec3 playerPos) override;
    virtual std::vector<CEnemyBullet*> shoot(glm::vec3 targetPos) override;
private:
    bool _flyDirection;//true向上飛、false向下
    float _flySpeed;
};
