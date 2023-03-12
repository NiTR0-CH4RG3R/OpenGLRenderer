#version 430 core
layout (location = 0) in vec3 i_color;


out vec4 FragColor;

void main() {
    FragColor = vec4(i_color, 1.0f);
}
