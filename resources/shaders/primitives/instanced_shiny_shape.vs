/* Shader that needs to receive a mat4 instanceModelMatrix
/* to be defined by Vertex Array in code
/* Same as "instanced_shape.vs" shader but transmitting vec3 position
/* for the fragment shader */

#version 330 core

layout(location=0)in vec3 pos;
layout(location=1)in mat4 instanceModelMatrix;

out vec3 position;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position=projection*view*instanceModelMatrix*vec4(pos,1.);
    position=pos;
}