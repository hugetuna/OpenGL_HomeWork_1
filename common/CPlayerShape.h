#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "CCircle.h"
#include "CTriangle.h"
#include "CTrapezoid.h"
#include "CHex.h"


class CPlayerShape {
public:
    CPlayerShape();
    ~CPlayerShape();

    void setupVertexAttributesAtOnce();
    void setShaderIDAtOnce(GLuint shaderID);
    void updateAtOnce(glm::vec3 pos, float dt);
    void drawAtOnce();
    //盾牌增減邏輯
    void removeOneShield();
    int getShieldCount(); // 可選，幫助外部查詢盾數
private:
    CTriangle* _hat;
    CCircle* _head;
    CTrapezoid* _cloak;
    //環繞盾牌
    CHex* _shields;
    int shieldCount;
    float shieldAngle;
};