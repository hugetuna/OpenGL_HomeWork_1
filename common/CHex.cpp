// CHex.cpp
#include <cmath>
#include <glew/include/GL/glew.h>
#include "CHex.h"

CHex::CHex() {
    _vtxCount = 6;
    _idxCount = 12; // 4 三角形覆蓋盾面（假設是六邊形拼成）

    _vtxAttrCount = 11; // pos(3) + color(3) + normal(3) + texcoord(2)
    _points = new GLfloat[_vtxCount * _vtxAttrCount];
    _idx = new GLuint[_idxCount];

    float radius = 0.2f;
    float angleStep = 360.0f / 6.0f;

    for (int i = 0; i < 6; ++i) {
        float angle = glm::radians(i * angleStep);
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        int offset = i * _vtxAttrCount;
        _points[offset] = x;
        _points[offset + 1] = y;
        _points[offset + 2] = 0.0f;

        _points[offset + 3] = 0.0f;
        _points[offset + 4] = 0.5f;
        _points[offset + 5] = 1.0f;

        _points[offset + 6] = 0.0f;
        _points[offset + 7] = 0.0f;
        _points[offset + 8] = 1.0f;

        _points[offset + 9] = (x + radius) / (2 * radius);
        _points[offset + 10] = (y + radius) / (2 * radius);
    }

    // 用中心點(0)構成三角形
    _idx[0] = 0; _idx[1] = 1; _idx[2] = 2;
    _idx[3] = 0; _idx[4] = 2; _idx[5] = 3;
    _idx[6] = 0; _idx[7] = 3; _idx[8] = 4;
    _idx[9] = 0; _idx[10] = 4; _idx[11] = 5;
}


CHex::~CHex() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
    if (_points) delete[] _points;
    if (_idx) delete[] _idx;
}

void CHex::draw() {
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}
void CHex::update(float dt)
{


}

void CHex::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}