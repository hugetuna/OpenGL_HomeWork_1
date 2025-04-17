#version 330 core

layout(location = 0) in vec3 aPos;      // 位置
layout(location = 1) in vec3 aColor;    // 顏色
layout(location = 2) in vec3 aNormal;   // 法向量
layout(location = 3) in vec2 aTexCoord; // 貼圖座標

uniform mat4 mxModel; // 模型變換矩陣
uniform mat4 mxView;  // 視角矩陣
uniform mat4 mxProj;  // 投影矩陣

out vec3 vColor;
out vec2 vTexCoord;

void main() {
    gl_Position = mxProj * mxView * mxModel * vec4(aPos, 1.0);
    vColor = aColor;
    vTexCoord = aTexCoord;
}