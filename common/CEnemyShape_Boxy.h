#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CEnemyShape.h"
#include "CCircle.h"

class CEnemyShape_Boxy : public CEnemyShape {
public:
    CEnemyShape_Boxy(GLuint shaderID);
    virtual ~CEnemyShape_Boxy();

    virtual void setupVertexAttributesAtOnce() override;
    virtual void setShaderIDAtOnce() override;
    virtual void updateAtOnce(glm::vec3 pos, float dt) override;
    virtual void drawAtOnce() override;

private:
    CQuad* _pBody;
    CCircle* _pEyeL;
    CCircle* _pEyeR;
    CStar* _pDecoration;
};


