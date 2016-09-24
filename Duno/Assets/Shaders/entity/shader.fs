#version 400
uniform sampler2D defuse;
uniform sampler2D bump;
in vec2 tex;
in vec3 pos;
in vec3 norm;

/* Point Lights */ 
uniform vec3 point_lightPos[10];
uniform vec3 point_lightColour[10];
uniform int point_length;
/* Dir Lights */
uniform vec3 dir_lightDir[10];
uniform int dir_length;

out vec4 Frag_Color;
void main(void) {
	vec3 normal = normalize(norm + texture( bump, vec2(tex.x, -tex.y) ).rgb*2.0 - 1.0);
	vec3 defuseLight = vec3(0,0,0);
	for (int i = 0; i < point_length; i++) {
		float dis = length(pos - point_lightPos[i]);
		float attFactor = 1.0 + (0.01 * dis) + (0.02 * (dis*dis));
		vec3 unitLightVector = normalize(pos - point_lightPos[i]);
		vec3 Kd = (max(dot(-normalize(normal), unitLightVector), 0) * point_lightColour[i])/attFactor;
		defuseLight += Kd;
	}
	//for (int i = 0; i < dir_length; i++) {
	//	vec3 unitLightVector = normalize(dir_lightDir[i]);
	//	vec3 Kd = (max(dot(-normalize(normal), unitLightVector), 0) * vec3(1,1,1));
	//	defuse += Kd;
	//}
	Frag_Color = texture(defuse, vec2(tex.x, -tex.y)) * vec4(defuseLight, 1);
}