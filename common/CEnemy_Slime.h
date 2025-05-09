#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CEnemy.h"
#include "CEnemyBullet.h"
#include "CEnemyShape_Slime.h"

class CEnemy_Slime :public CEnemy {
public:
    CEnemy_Slime(GLuint shaderID);
    ~CEnemy_Slime();
    virtual void update(float dt, glm::vec3 playerPos) override;
    virtual std::vector<CEnemyBullet*> shoot(glm::vec3 targetPos) override;
private:
    float _moveSpeed;
    bool _bAttackWay;//true為上三角，false為下三角
};
