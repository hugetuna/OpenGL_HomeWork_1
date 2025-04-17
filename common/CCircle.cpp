#include <cmath>
#include <glew/include/GL/glew.h>
#include "CCircle.h"

#define PI 3.14159265358979f

CCircle::CCircle(int segments) : CShape(), _segments(segments) {
    _vtxCount = segments + 2; // 中心點 + 邊界點們
    _vtxAttrCount = 11;
    _idxCount = segments * 3;

    _points = new GLfloat[_vtxCount * _vtxAttrCount];
    _idx = new GLuint[_idxCount];

    // 中心點
    _points[0] = 0.0f; _points[1] = 0.0f; _points[2] = 0.0f;     // 位置
    _points[3] = 1.0f; _points[4] = 1.0f; _points[5] = 1.0f;     // 顏色
    _points[6] = 0.0f; _points[7] = 0.0f; _points[8] = 1.0f;     // 法向量
    _points[9] = 0.5f; _points[10] = 0.5f;                       // 貼圖座標中心

    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = cos(angle) * 0.5f;
        float y = sin(angle) * 0.5f;

        int offset = (i + 1) * _vtxAttrCount;
        _points[offset] = x;
        _points[offset + 1] = y;
        _points[offset + 2] = 0.0f;
        _points[offset + 3] = 1.0f;
        _points[offset + 4] = 1.0f;
        _points[offset + 5] = 1.0f;
        _points[offset + 6] = 0.0f;
        _points[offset + 7] = 0.0f;
        _points[offset + 8] = 1.0f;
        _points[offset + 9] = x + 0.5f;
        _points[offset + 10] = y + 0.5f;
    }

    for (int i = 0; i < segments; ++i) {
        _idx[i * 3] = 0;
        _idx[i * 3 + 1] = i + 1;
        _idx[i * 3 + 2] = i + 2;
    }

    // setupVertexAttributes(); 呼叫者再呼叫
}

CCircle::~CCircle() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
    if (_points) delete[] _points;
    if (_idx) delete[] _idx;
}

void CCircle::draw() {
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CCircle::update(float dt)
{


}

void CCircle::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}