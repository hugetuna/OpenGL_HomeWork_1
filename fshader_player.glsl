#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

//�{�{�X��
uniform bool u_Flash;

void main() {
    vec4 baseColor = vec4(vColor, 1.0);//�ǤJ�����I�C��

    if (u_Flash) {
        // �{�{���ܫG�]�զ�{���^
        baseColor = mix(baseColor, vec4(1.0, 1.0, 1.0, 1.0), 0.7);
    }

    FragColor = baseColor;
}