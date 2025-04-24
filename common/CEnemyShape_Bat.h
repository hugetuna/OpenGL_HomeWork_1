#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "CEnemyShape.h"


class CEnemyShape_Bat : public CEnemyShape {
public:

    CEnemyShape_Bat(GLuint shaderID);
    ~CEnemyShape_Bat();
    virtual void setupVertexAttributesAtOnce() override;
    virtual void setShaderIDAtOnce() override;
    virtual void updateAtOnce(glm::vec3 pos, float dt) override;
    virtual void drawAtOnce() override;
private:
    //todo:繼承後實作形狀
    CCircle* _pHead;
    CCircle* _pEye;
    CTriangle* _pWingLeft;
    CTriangle* _pWingRight;
};
