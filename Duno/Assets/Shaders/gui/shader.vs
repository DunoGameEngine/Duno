#version 400
in vec2 position;
uniform mat4 m;

out vec2 tex;
void main(void) {
	gl_Position = m * vec4(vec3(position, 0.0), 1.0);
	tex = vec2(position.x, -position.y);
}
