#pragma once

#include <glew/include/GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "CCircle.h"
#include "CTriangle.h"
#include "CTrapezoid.h"
#include "CHex.h"
#include "CStar.h"


class CPlayerShape {
public:
    CPlayerShape();
    ~CPlayerShape();

    void setupVertexAttributesAtOnce();
    void setShaderIDAtOnce(GLuint shaderID);
    void updateAtOnce(glm::vec3 pos, float dt);
    void drawAtOnce();
    //�޵P�W���޿�
    void removeOneShield();
    int getShieldCount(); // �i��A���U�~���d�߬޼�
    void changeHat(); // �����U�l
private:
    //�U�l�C��
    std::vector<CShape*> _hatList;
    int _hatOnHead = 0; // ��e�襤���U�l

    CCircle* _head;
    CTrapezoid* _cloak;
    //��¶�޵P
    CHex* _shields;
    int shieldCount;
    float shieldAngle;
};