#version 330 core

out vec4 FragColor;

uniform vec3 color;

uniform int textureDefined;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
    if (textureDefined == 1)
        FragColor = texture(ourTexture, TexCoord) * vec4(color, 1.0f);
    else
        FragColor = vec4(color, 1.0f);
}