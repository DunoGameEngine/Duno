#version 400
uniform samplerCube defuse;
in vec3 tex;

out vec4 out_Color;
void main(void) {
	out_Color = texture(defuse, tex);
}