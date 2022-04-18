#version 420 core

void main(void)
{
    const vec4 vertices[]=vec4[](vec4(.25,-.25,.5,1.),
    vec4(-.25,-.25,.5,1.),
    vec4(.25,.25,.5,1.));
    
    gl_Position=vertices[gl_VertexID];
}