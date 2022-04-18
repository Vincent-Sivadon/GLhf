/* For a Disk : fancy graph node */

#version 330 core

out vec4 FragColor;

in vec3 position;

// Will be useless here
uniform vec3 color;

void main()
{
    float r=length(position);
    
    float glow=.3/r;
    glow=clamp(glow,0.,1.);
    
    float newColor=cos(150.*r*(1.-r));
    newColor*=glow;
    
    float st=1.-step(.5,r);
    newColor+=200.*st;
    
    FragColor=vec4(color*newColor,.9f);
}