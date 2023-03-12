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

void main() {
    vec3 v_to_l = normalize( u_f3PLposition - i_v3ViewPosition );
    float dist = length( v_to_l );
    float fAttenuation = 1.0 / (u_f3PLattenuation.z + u_f3PLattenuation.y * dist + u_f3PLattenuation.x * ( dist * dist ));
    vec3 d = u_f3PLcolor * fAttenuation * max(0.0, dot( i_v3Normal, v_to_l ));

    	// Reflected light vector
	vec3 w = i_v3Normal * dot( v_to_l, i_v3Normal );
	vec3 r = normalize( (w * 2.0) - v_to_l );
	vec3 vertex_view_pos = normalize( i_v3ViewPosition );

	// Calculate specular
	vec3 s = u_f3PLcolor * u_fSpecularIntensity  * fAttenuation *
		pow(
			max(0.0, dot(-r, vertex_view_pos)),
			u_fSpecularPower
		);

	vec3 hammard_in = d + u_f3PLambiant + s;
	//const Math::Vector3 hammard_in = d + PointLightAmbiant ;

	// Get the hammard of the pixel
	vec3 hammard = vec3(
		u_f3Mcolor.x *	hammard_in.x,
		u_f3Mcolor.y *	hammard_in.y,
		u_f3Mcolor.z *	hammard_in.z
	);

	vec3 color = vec3(
		min(1.0, max(hammard.x, 0.0)),
		min(1.0, max(hammard.y, 0.0)),
		min(1.0, max(hammard.z, 0.0))
	);

    FragColor = vec4(color, 1.0);
}
