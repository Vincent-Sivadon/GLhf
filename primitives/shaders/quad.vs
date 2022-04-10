#version 410 core

layout(location=0)in vec3 pos;

out vec4 color;

uniform mat4 modelView;
uniform mat4 projection;

void main(void)
{
    gl_Position=projection*modelView*vec4(pos,1.f);
    color=vec4(pos,1.f)*2.+vec4(.5,.5,.5,0.);
}