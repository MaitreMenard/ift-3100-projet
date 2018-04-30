#version 150

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
	float red, green, blue;
	vec4 color = texture(tex0, texCoordVarying);
	
	red = (color.r * 0.393) + (color.g * 0.769) + (color.b * 0.189);
	green = (color.r * 0.349) + (color.g * 0.686) + (color.b * 0.168);
	blue = (color.r * 0.272) + (color.g * 0.534) + (color.b * 0.131);
	
    outputColor = vec4(red, green, blue, color.a);
}