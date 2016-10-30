#version 400

in vec3 position;
in vec2 textureCoords;
in vec3 normal;
in vec3 tangent;

uniform vec3 point_lightPos[10];
uniform int point_length;
uniform vec3 cam_position;
uniform mat4 m;
out vec3 point_toLightPos[10];

uniform mat4 mvp;
out vec2 tex;
out vec3 pos;
out vec3 norm;
out mat3 toTangentSpace;
//out vec3 toCam;
void main(void) {
	gl_Position = mvp * vec4(position, 1.0);
	tex = textureCoords;
	pos = position;
	norm = normal;
	
	vec3 n = normalize(normal);
	vec3 t = normalize(tangent);
	vec3 bt = normalize(cross(n, t));
	toTangentSpace = mat3(
		t.x, bt.x, n.x,
		t.y, bt.y, n.y,
		t.z, bt.z, n.z
	);
	//toCam = toTangentSpace * normalize(cam_position - position);
	for (int i = 0; i < point_length; i++) {
		point_toLightPos[i] = toTangentSpace * (point_lightPos[i] - (m * vec4(position, 1.0)).xyz);
	}
}