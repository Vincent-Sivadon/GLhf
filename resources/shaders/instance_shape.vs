#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in mat4 aInstanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position=projection*view*aInstanceMatrix*vec4(aPos,.9f);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal; 
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
}