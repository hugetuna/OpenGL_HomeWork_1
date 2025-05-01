#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include "CCircle.h"
#include "CEnemy.h"
#include "CBossShape.h"
class CBoss : public CEnemy {
public:
    CBoss(GLuint shaderID);
    ~CBoss();
    virtual void update(float dt, glm::vec3 playerPos) override;
    virtual std::vector<CEnemyBullet*> shoot(glm::vec3 targetPos) override;
    bool readyToShoot() override;

private:
    float _moveSpeed;
    int _stage;
};




