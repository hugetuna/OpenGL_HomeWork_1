#include <cmath>
#include <glew/include/GL/glew.h>


#include "CStar.h"

CStar::CStar(int points, float outerRadius, float innerRadius) {
    const float PI = 3.1415926f;
    int totalPoints = points * 2;  // 一個尖角一個凹角

    _vtxCount = totalPoints + 1;  // 中心點 + 所有邊緣點
    _vtxAttrCount = 11;
    _idxCount = totalPoints * 3;  // 每個扇形三角形 3 點

    _points = new GLfloat[_vtxCount * _vtxAttrCount];
    _idx = new GLuint[_idxCount];

    // 中心點
    _points[0] = 0.0f; _points[1] = 0.0f; _points[2] = 0.0f;  // 位置
    _points[3] = 1.0f; _points[4] = 1.0f; _points[5] = 1.0f;  // 顏色
    _points[6] = 0.0f; _points[7] = 0.0f; _points[8] = 1.0f;  // 法向量
    _points[9] = 0.5f; _points[10] = 0.5f;  // 貼圖座標

    // 外圓和內圓的點
    for (int i = 0; i < totalPoints; ++i) {
        float angle = i * PI / points;
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;  // 交替使用外圓與內圓半徑

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

    // 設置三角形索引
    for (int i = 0; i < totalPoints; ++i) {
        _idx[i * 3] = 0;
        _idx[i * 3 + 1] = i + 1;
        _idx[i * 3 + 2] = (i + 1) % totalPoints + 1;
    }
}

CStar::~CStar() {
    // 記得清理資源
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
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);  // 繪製圖形
}

void CStar::update(float dt) {
    // 如果有需要，這裡可以進行動畫或其他更新邏輯
}

void CStar::reset() {
    CShape::reset();
    // 如有需要，可以加入其他重設的邏輯
}
