#include <cmath>
#include <glew/include/GL/glew.h>


#include "CStar.h"

CStar::CStar(int points, float outerRadius, float innerRadius) {
    const float PI = 3.1415926f;
    int totalPoints = points * 2;  // �@�Ӧy���@�ӥW��

    _vtxCount = totalPoints + 1;  // �����I + �Ҧ���t�I
    _vtxAttrCount = 11;
    _idxCount = totalPoints * 3;  // �C�Ӯ��ΤT���� 3 �I

    _points = new GLfloat[_vtxCount * _vtxAttrCount];
    _idx = new GLuint[_idxCount];

    // �����I
    _points[0] = 0.0f; _points[1] = 0.0f; _points[2] = 0.0f;  // ��m
    _points[3] = 1.0f; _points[4] = 1.0f; _points[5] = 1.0f;  // �C��
    _points[6] = 0.0f; _points[7] = 0.0f; _points[8] = 1.0f;  // �k�V�q
    _points[9] = 0.5f; _points[10] = 0.5f;  // �K�Ϯy��

    // �~��M���ꪺ�I
    for (int i = 0; i < totalPoints; ++i) {
        float angle = i * PI / points;
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;  // ����ϥΥ~��P����b�|

        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        int offset = (i + 1) * _vtxAttrCount;
        _points[offset + 0] = x;
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

    // �]�m�T���ί���
    for (int i = 0; i < totalPoints; ++i) {
        _idx[i * 3] = 0;
        _idx[i * 3 + 1] = i + 1;
        _idx[i * 3 + 2] = (i + 1) % totalPoints + 1;
    }
}

CStar::~CStar() {
    // �O�o�M�z�귽
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
    if (_points) delete[] _points;
    if (_idx) delete[] _idx;
}

void CStar::draw() {
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);  // ø�s�ϧ�
}

void CStar::update(float dt) {
    // �p�G���ݭn�A�o�̥i�H�i��ʵe�Ψ�L��s�޿�
}

void CStar::reset() {
    CShape::reset();
    // �p���ݭn�A�i�H�[�J��L���]���޿�
}
