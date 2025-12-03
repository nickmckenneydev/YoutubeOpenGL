#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 tex1 = texture(texture1, TexCoord);
    vec4 tex2 = texture(texture2, TexCoord);

    // Use tex2.a (alpha) to decide mixing. 
    // If tex2 is transparent (alpha=0), show tex1. 
    // If tex2 is opaque (alpha=1), show tex2.
    FragColor = mix(tex1, tex2, tex2.a);
}