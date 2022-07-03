#version 450 core

in vec2 screenSize;

out vec4 outputColor;

void main()
{
    vec2 color = gl_FragCoord.xy / vec2(1600, 900);
    outputColor = vec4(color.xy, 1, 1);
}