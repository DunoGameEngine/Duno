#version 400
uniform sampler2D defuse;
uniform sampler2D bump;
in vec2 tex;
in mat3 toTangentSpace;

/* Point Lights */ 
in vec3 point_toLightPos[10];
uniform vec3 point_lightColour[10];
uniform int point_length;
/* Dir Lights */
uniform vec3 dir_lightDir[10];
uniform int dir_length;

out vec4 Frag_Color;
void main(void) {
	vec3 normal = normalize((2 * texture(bump, vec2(tex.x, -tex.y)) - 1.0).rgb);
	vec3 defuseLight = vec3(0,0,0);
	
	for (int i = 0; i < point_length; i++) {
		float dis = length(point_toLightPos[i]);
		float attFactor = 1.0 + (0.01 * dis) + (0.02 * (dis*dis));
		vec3 unitLightVector = normalize(point_toLightPos[i]);
		vec3 Kd = (max(dot(normal, unitLightVector), 0) * point_lightColour[i])/attFactor;
		defuseLight += Kd;
	}
	for (int i = 0; i < dir_length; i++) {
		vec3 unitLightVector = normalize(toTangentSpace * dir_lightDir[i]);
		vec3 Kd = max(dot(-normal, unitLightVector), 0) * vec3(1,1,1);
		defuseLight += Kd;
	}
	defuseLight = max(defuseLight, 0.1);
	Frag_Color = texture(defuse, vec2(tex.x, -tex.y)) * vec4(defuseLight, 1);
}