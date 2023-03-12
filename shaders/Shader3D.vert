#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 0) uniform mat4 transform;

layout (location = 0) out vec3 o_color;

void main() {
   gl_Position = transform * vec4(position.x, position.y, position.z, 1.0) ;
   o_color = normal;
}
