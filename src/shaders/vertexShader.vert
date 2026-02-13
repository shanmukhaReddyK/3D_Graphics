#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float loopDuration;
uniform float time;

out vec3 ourColor;

void main()
{
    float timeScale = 3.14159f * 2.0f / loopDuration;
    
    float currTime = mod(time, loopDuration);

    vec4 totalOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);

    gl_Position = vec4(aPos, 1.0) + totalOffset;
    ourColor = aColor;
}