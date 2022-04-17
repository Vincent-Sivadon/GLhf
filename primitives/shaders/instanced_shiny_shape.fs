#version 330 core

out vec4 FragColor;

in vec3 position;

// Will be useless here
uniform vec3 color;

void main()
{
    float r=.5f*length(position);
    
    FragColor=vec4(color*glm::vec3(1.f-r),1.f);
}