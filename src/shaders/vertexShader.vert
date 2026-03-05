#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 perspectiveMatrix;

void main()
{
    gl_Position = perspectiveMatrix * (position + vec4(1.50f, 0.50f, 0, 0));
    theColor = color;
}