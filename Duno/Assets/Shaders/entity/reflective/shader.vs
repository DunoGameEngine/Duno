#version 400

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

uniform mat4 mvp;
uniform vec3 cameraPosition;
out vec2 tex;
out vec3 pos;
out vec3 norm;
out vec3 reflectedVector;
void main(void) {
	vec4 worldPosition = mvp * vec4(position, 1.0);
	gl_Position = worldPosition;
	reflectedVector = reflect(normalize(worldPosition.xyz - (-cameraPosition)), normalize(normal));
	tex = textureCoords;
	norm = normal;
	pos = position;
}