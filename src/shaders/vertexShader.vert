#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;
uniform mat4 worldToCameraMatrix;

void main()
{	
	vec4 cameraPos = modelToCameraMatrix  * position;
	cameraPos = worldToCameraMatrix * cameraPos;
	gl_Position = cameraToClipMatrix * cameraPos;
	theColor = color;
}