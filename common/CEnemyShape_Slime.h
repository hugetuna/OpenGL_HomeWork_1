#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CEnemyShape.h"

class CEnemyShape_Slime : public CEnemyShape {
public:
    CEnemyShape_Slime(GLuint shaderID);
    virtual ~CEnemyShape_Slime();

    virtual void setupVertexAttributesAtOnce() override;
    virtual void setShaderIDAtOnce() override;
    virtual void updateAtOnce(glm::vec3 pos, float dt) override;
    virtual void drawAtOnce() override;

private:
    CCircle* _pBody;
    CCircle* _pEyeL;
    CCircle* _pEyeR;
    CTrapezoid* _pMouth;
};

