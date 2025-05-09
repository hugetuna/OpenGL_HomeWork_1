#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0); // 顯示傳入的頂點顏色
}