#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0); // ��ܶǤJ�����I�C��
}