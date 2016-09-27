#version 400
in vec3 position;

uniform mat4 mvp;
out vec3 tex;
void main(void) {
	gl_Position = mvp * vec4(position, 1.0);
	tex = position;
}
