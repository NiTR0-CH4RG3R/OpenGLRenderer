#version 430 core
layout (location = 0) in vec3 position;
layout (location = 0) uniform mat4 transform;

void main() {
   gl_Position = transform * vec4(position.x, position.y, position.z, 1.0) ;
}
