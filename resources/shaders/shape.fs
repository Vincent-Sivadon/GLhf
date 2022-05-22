#version 330 core

out vec4 FragColor;
in vec3 FragPos;

uniform vec3 color;
uniform sampler2D ourTexture;

in vec2 TexCoord;
in vec3 Normal;

void main()
{
    // Hard coded light caracteristics
    vec3 lightpos = vec3(3.0f, 3.0f, -3.0f);
    vec3 lightcolor = vec3(1.0f);
    float ambientstrenght = 0.1;
    vec3 ambient = ambientstrenght * lightcolor;

    vec3 norm = normalize(Normal);
    vec3 lightdir = normalize(lightpos - FragPos);
    float diff = max(dot(norm, lightdir), 0.0);
    vec3 diffuse = diff * lightcolor;
    
    vec3 result = (ambient + diffuse) * color;

    FragColor = texture(ourTexture, TexCoord) * vec4(color, 1.0f);
}