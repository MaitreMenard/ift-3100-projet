#version 150

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
	vec3 factor = vec3(3.0, 3.0, 3.0);
	vec3 color = floor(texture(tex0, texCoordVarying).rgb * factor) / factor;
    outputColor = vec4(color, texture(tex0, texCoordVarying).a);
}