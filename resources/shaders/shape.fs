#version 330 core

out vec4 FragColor;
in vec3 FragPos;

uniform vec3 color;
uniform vec3 camera_pos;
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

    // Specular
    float specularStrength = 0.5;
    vec3 view_direction = normalize(camera_pos - FragPos);
    vec3 reflection_direction = reflect(-lightdir, norm);
    float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;

    vec3 result = (ambient + diffuse + specular) * color;

    FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0f);
}