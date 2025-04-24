#pragma once

#include <glew/include/GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CCircle.h"
#include "CTriangle.h"
#include "CTrapezoid.h"
#include "CQuad.h"
#include "CHex.h"
#include "CStar.h"

class CEnemyShape {
public:
    CEnemyShape(GLuint shaderID);
    virtual ~CEnemyShape();

    virtual void setupVertexAttributesAtOnce() = 0;
    virtual void setShaderIDAtOnce() = 0;
    virtual void updateAtOnce(glm::vec3 pos, float dt) = 0;
    virtual void drawAtOnce() = 0;

protected:
    GLuint _shaderID;
};

