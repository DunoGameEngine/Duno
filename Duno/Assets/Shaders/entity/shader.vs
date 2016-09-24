#version 400

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

uniform mat4 mvp;
out vec2 tex;
out vec3 pos;
out vec3 norm;
void main(void) {
	gl_Position = mvp * vec4(position, 1.0);
	tex = textureCoords;
	norm = normal;
	pos = position;
}