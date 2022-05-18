/* Shader that needs to receive a mat4 instanceModelMatrix
/* to be defined by Vertex Array in code */

#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;
layout(location=2) in mat4 aInstanceModelMatrix;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position=projection*view*aInstanceModelMatrix*vec4(aPos,1.);
}