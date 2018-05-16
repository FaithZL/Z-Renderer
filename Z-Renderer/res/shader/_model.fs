#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{
    color = vec4(texture(texture_diffuse1, TexCoords).rgb , 1.0);
//    color = vec4(1 , 0.5 , 0.2 , 1);
}
