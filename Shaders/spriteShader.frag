#version 430 core

in vec2 tCoords;

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, tCoords);
	fragColor = vec4(vec3(texColor) * color, texColor.w);
}