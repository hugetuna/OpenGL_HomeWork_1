#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

//閃爍旗標
uniform bool u_Flash;

void main() {
    vec4 baseColor = vec4(vColor, 1.0);//傳入的頂點顏色

    if (u_Flash) {
        // 閃爍時變亮（白色閃光）
        baseColor = mix(baseColor, vec4(1.0, 1.0, 1.0, 1.0), 0.7);
    }

    FragColor = baseColor;
}