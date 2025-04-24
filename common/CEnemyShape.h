#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CCircle.h"
#include "CTriangle.h"
#include "CTrapezoid.h"
#include "CHex.h"


class CEnemyShape {
public:
    CEnemyShape(GLuint shaderID);
    ~CEnemyShape();

    virtual void setupVertexAttributesAtOnce();
    virtual void setShaderIDAtOnce();
    virtual void updateAtOnce(glm::vec3 pos, float dt);
    virtual void drawAtOnce();

protected:
    GLuint _shaderID;
};
