#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uvs;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 out_normal;
out vec2 out_texture;

void main()
{
	gl_Position = projection * view * model * vec4(vertex.xyz, 1);
	out_normal = model * vec4(normal.xyz, 0);
	out_texture = uvs;
}