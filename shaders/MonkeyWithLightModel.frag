#version 430 core

layout (location = 0) in vec3 i_v3ViewPosition;
layout (location = 1) in vec3 i_v3Normal;
layout (location = 2) in vec2 i_v2UV;

uniform vec3 u_f3PLposition;
uniform vec3 u_f3PLcolor;
uniform vec3 u_f3PLambiant;
uniform vec3 u_f3PLattenuation;
uniform vec3 u_f3Mcolor;

uniform float u_fSpecularIntensity;
uniform float u_fSpecularPower;

out vec4 FragColor;

vec3 GetHammard( vec3 i, vec3 j ) {
    return vec3(
                i.x * j.x,
                i.y * j.y,
                i.z * j.z
                );
}

vec3 Saturate( vec3 i ) {
    return vec3(
        min(1.0, max(i.x, 0.0)),
		min(1.0, max(i.y, 0.0)),
		min(1.0, max(i.z, 0.0))
                );
}

void main() {
    vec3 v3Normal = normalize( i_v3Normal );
    vec3 L = i_v3ViewPosition - u_f3PLposition;


    float dist = abs(length( L ));
	float Attenuation = 1.0 /
		(u_f3PLattenuation.z + u_f3PLattenuation.y * dist + u_f3PLattenuation.x * pow( dist, 2 ));

    vec3 d = u_f3PLcolor * Attenuation * dot(  v3Normal,  normalize( -L ) );

    vec3 R = 2 * ( dot( L, v3Normal) ) * v3Normal - L;
    vec3 s = u_f3PLcolor * u_fSpecularIntensity * pow( max( 0.0, dot( normalize( R ), normalize( i_v3ViewPosition ) ) ), u_fSpecularPower );
    vec3 v3SpecularAmbient = d + u_f3PLambiant + s;




    vec3 v3Color = u_f3Mcolor * min( 1.0, max( 0.0, dot(  normalize( -L ), v3Normal ) ) );

    vec3 v3SpecularColor = Saturate( GetHammard( u_f3Mcolor, v3SpecularAmbient ) );
    FragColor = vec4( v3SpecularColor, 1.0);
}
