#include <glew/include/GL/glew.h>
#include "CTrapezoid.h"

CTrapezoid::CTrapezoid() : CShape() {
    _vtxCount = 4;
    _vtxAttrCount = 11;
    _idxCount = 6;

    _points = new GLfloat[_vtxCount * _vtxAttrCount];
    _idx = new GLuint[_idxCount];

    // �]�w 4 ���I�G���䬰 1.0�A�W�䬰 0.5�A���� 1.0�A�m��
    GLfloat verts[4][3] = {
        {-0.5f, -0.5f, 0.0f},  // ���U
        { 0.5f, -0.5f, 0.0f},  // �k�U
        {-0.25f, 0.5f, 0.0f},  // ���W
        { 0.25f, 0.5f, 0.0f}   // �k�W
    };

    for (int i = 0; i < 4; ++i) {
        int offset = i * _vtxAttrCount;
        _points[offset + 0] = verts[i][0];  // x
        _points[offset + 1] = verts[i][1];  // y
        _points[offset + 2] = verts[i][2];  // z
        _points[offset + 3] = 0;         // r
        _points[offset + 4] = 0;         // g
        _points[offset + 5] = 1.0f;         // b
        _points[offset + 6] = 0.0f;         // nx
        _points[offset + 7] = 0.0f;         // ny
        _points[offset + 8] = 1.0f;         // nz
        _points[offset + 9] = verts[i][0] + 0.5f;  // u
        _points[offset + 10] = verts[i][1] + 0.5f; // v
    }

    // ���ޡG������ӤT����
    _idx[0] = 0; _idx[1] = 1; _idx[2] = 2;
    _idx[3] = 1; _idx[4] = 3; _idx[5] = 2;

    // setupVertexAttributes(); �I�s�̦A�I�s
}

CTrapezoid::~CTrapezoid() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
    if (_points) delete[] _points;
    if (_idx) delete[] _idx;
}

void CTrapezoid::draw() {
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CTrapezoid::update(float dt)
{


}

void CTrapezoid::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}