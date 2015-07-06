#version 330 core
#extension GL_ARB_explicit_uniform_location : require
#extension GL_ARB_separate_shader_objects: enable

in vec4 out_color;
out vec4 frag_color;

void main()
{
	frag_color = out_color;
}