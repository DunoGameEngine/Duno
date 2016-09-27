#version 400
uniform sampler2D defuse;
in vec2 tex;
in float test;

out vec4 Frag_Color;
void main(void) {
	Frag_Color = texture(defuse, tex)*vec4(test,test,test,1);
}