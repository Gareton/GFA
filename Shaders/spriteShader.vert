#version 430 core

layout(location = 0) in vec4 vertex; // pos, tCoords

out vec2 tCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat3 texMatrix;

void main()
{
	gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
	//gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
	vec3 tTransformed = texMatrix * vec3(vertex.zw, 1.0f);
	tCoords = vec2(tTransformed);
}