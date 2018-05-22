#version 330 core
layout (location = 0) out vec4 color;

uniform vec2 light_pos;

// Ouput data

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main() {

	float intensity = 2.0f / length(fs_in.position.xy - light_pos);
	color = fs_in.color;

}