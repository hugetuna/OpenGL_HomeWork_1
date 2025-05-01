#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CEnemy.h"
#include "CEnemyBullet.h"
#include "CEnemyShape_Boxy.h"

class CEnemy_Boxy :public CEnemy {
public:
    CEnemy_Boxy(GLuint shaderID);
    ~CEnemy_Boxy();
    virtual void update(float dt, glm::vec3 playerPos) override;
    virtual std::vector<CEnemyBullet*> shoot(glm::vec3 targetPos) override;
private:
    float _moveTime;
};
