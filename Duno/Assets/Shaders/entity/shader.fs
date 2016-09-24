#version 400
uniform sampler2D defuse;
uniform sampler2D bump;
in vec2 tex;
in vec3 pos;
in vec3 norm;

uniform vec3 lightPos;

out vec4 Frag_Color;
void main(void) {
	vec3 normal = normalize(norm + texture( bump, vec2(tex.x, -tex.y) ).rgb*2.0 - 1.0);
	float dis = length(pos - lightPos);
	float attFactor = 1.0 + (0.01 * dis) + (0.02 * (dis*dis));
	vec3 unitLightVector = normalize(pos - lightPos);
	vec3 Kd = (max(dot(-normalize(normal), unitLightVector), 0) * vec3(1,1,1))/attFactor;
	Frag_Color = texture(defuse, vec2(tex.x, -tex.y)) * vec4(Kd, 1);
}