#version 330 core
#extension GL_ARB_explicit_uniform_location : require
#extension GL_ARB_separate_shader_objects: enable

in vec2 text_coord;
smooth in vec3 vNormal;
out vec4 frag_color;

uniform sampler2D diffuse;
uniform vec4 vColor;

struct SimpleDirectionalLight
{
	vec3 vColor;
	vec3 vDirection;
	float fAmbientIntensity;
};

uniform SimpleDirectionalLight sunLight;

void main()
{
	vec4 vTexColor = texture2D(diffuse, text_coord);
	float fDiffuseIntensity = max(0.0, dot(normalize(vNormal), -sunLight.vDirection));
	//frag_color = vTexColor*vColor*vec4(sunLight.vColor*(sunLight.fAmbientIntensity+fDiffuseIntensity), 1.0); 
	vec4 matrix = vec4(sunLight.vColor*(sunLight.fAmbientIntensity+fDiffuseIntensity), 1.0);
	frag_color = vTexColor*vColor*matrix;//*matrix;//vec4(0.25,0.250,0.25,1.0);//*matrix; 

}