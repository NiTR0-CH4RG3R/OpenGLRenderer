#version 430 core
layout (location = 0) in vec3 i_v3Position;
layout (location = 1) in vec3 i_v3Normal;
layout (location = 2) in vec2 i_v2UV;

uniform mat4 u_m4TransformMatrix;
uniform mat4 u_m4ViewMatrix;
uniform mat4 u_m4NormalTransformMatrix;

layout (location = 0) out vec3 o_v3ViewPosition;
layout (location = 1) out vec3 o_v3Normal;
layout (location = 2) out vec2 o_v2UV;

void main() {
   gl_Position = u_m4TransformMatrix * vec4(i_v3Position, 1.0) ;
   o_v3ViewPosition = (u_m4ViewMatrix * vec4(i_v3Position, 1.0)).xyz;
   //o_v3ViewPosition = i_v3Position;
   o_v3Normal = ( u_m4NormalTransformMatrix * vec4( i_v3Normal, 1.0 ) ).xyz;
   //o_v3Normal = i_v3Normal;
   o_v2UV = i_v2UV;
}
