#version 400
uniform sampler2D defuse;
uniform sampler2D bump;
uniform sampler2D spec_map;
in vec2 tex;
in vec3 pos;
in vec3 norm;
in mat3 toTangentSpace;

/* Point Lights */ 
uniform vec3 point_lightPos[10];
in vec3 point_toLightPos[10];
uniform vec3 point_lightColour[10];
uniform int point_length;
/* Dir Lights */
uniform vec3 dir_lightDir[10];
uniform int dir_length;

uniform mat4 m;
uniform vec3 ambient_light;
uniform vec3 cam_position;
uniform float shininess;
uniform float light_emitted;

out vec4 Frag_Color;

vec4 ads(vec4 defuse, vec3 normal, float specAmount)
{
	vec3 defuseLight = vec3(0,0,0);
	vec3 specularLight = vec3(0,0,0);
	
	for (int i = 0; i < point_length; i++) {
		vec3 s = normalize(point_toLightPos[i]);
		float dis = length(point_toLightPos[i]);
		float attFactor = 1.0 + (0.01 * dis) + (0.02 * (dis*dis));
		vec3 toCam = normalize(point_toLightPos[i] - (toTangentSpace * (cam_position + point_lightPos[i])));
		specularLight += point_lightColour[i] * ((max(pow(dot(reflect(-s, normal), toCam), 20), 0.0) * shininess) / attFactor);
		defuseLight += point_lightColour[i] * ((max(dot(s, normal), 0.0)) / attFactor);
	}
	defuseLight = max(defuseLight, light_emitted);
	
	return vec4(defuseLight, 1.0) * defuse + vec4(specularLight * specAmount, 1.0);
}

subroutine vec4 shadeModelType(vec4 defuse);
subroutine uniform shadeModelType shadeModel;
subroutine (shadeModelType)
vec4 basic(vec4 defuse) {
	return ads(defuse, vec3(0, 0, 1), 1.0);
}
subroutine (shadeModelType)
vec4 bumped(vec4 defuse) {
	vec3 normal = normalize((2 * texture(bump, tex) - 1.0).rgb);
	return ads(defuse, normal, 1.0);
}
subroutine (shadeModelType)
vec4 full(vec4 defuse) {
	vec3 normal = normalize((2 * texture(bump, tex) - 1.0).rgb);
	float specAmount = texture(spec_map, tex).r;
	return ads(defuse, normal, specAmount);
}

void main(void) {	
	Frag_Color = shadeModel(texture(defuse, tex));
}