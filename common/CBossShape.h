#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "CCircle.h"
#include "CStar.h"
#include "CTriangle.h"
#include "CEnemyShape.h"

class CBossShape:public CEnemyShape {
public:
    CBossShape(GLuint shaderID);
    ~CBossShape();

    void setStage(int stage); // 1~3
    virtual void setupVertexAttributesAtOnce() override;
    virtual void setShaderIDAtOnce()override;
    virtual void updateAtOnce(glm::vec3 pos, float dt)override;
    virtual void drawAtOnce() override;

private:
    int _stage = 1;

    // 組成部件
    CCircle* _outerCircle;
    CCircle* _innerCircle;

    CStar* _outerStar;
    CStar* _innerStar;

    CTriangle* _leftWing;
    CTriangle* _rightWing;
};



