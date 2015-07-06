#version 330 core
#extension GL_ARB_explicit_uniform_location : require

uniform mat4 model;
uniform mat4 prespective;
uniform mat4 camera;
uniform mat4 normalMatrix;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 inNormal;
//in vec4 color;
out vec2 text_coord;
smooth out vec3 vNormal;
void main() {
    // does not alter asdasdthe verticies at all
    gl_Position = prespective*camera*model*vec4(vPosition, 1);
    text_coord = textCoord;
    vec4 vRes = normalMatrix*vec4(inNormal, 0.0);
    vNormal = vRes.xyz;
}