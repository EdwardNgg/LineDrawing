#version 410 core

layout (location = 0) in vec2 aPos;

uniform float windowWidth;

uniform float windowHeight;

void main()
{
    // transform screen-space coordinate into NDC
    gl_Position = vec4(2.0f * aPos.x / windowWidth - 1.0f,
                       2.0f * aPos.y / windowHeight - 1.0f,
                       0.0f,
                       1.0f);
}

