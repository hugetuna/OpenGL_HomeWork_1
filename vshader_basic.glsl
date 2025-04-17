#version 330 core

layout(location = 0) in vec3 aPos;      // ��m
layout(location = 1) in vec3 aColor;    // �C��
layout(location = 2) in vec3 aNormal;   // �k�V�q
layout(location = 3) in vec2 aTexCoord; // �K�Ϯy��

uniform mat4 mxModel; // �ҫ��ܴ��x�}
uniform mat4 mxView;  // �����x�}
uniform mat4 mxProj;  // ��v�x�}

out vec3 vColor;
out vec2 vTexCoord;

void main() {
    gl_Position = mxProj * mxView * mxModel * vec4(aPos, 1.0);
    vColor = aColor;
    vTexCoord = aTexCoord;
}