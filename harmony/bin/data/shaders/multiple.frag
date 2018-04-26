#version 330	

uniform sampler2DRect tex0;
uniform sampler2DRect texEdge;

in vec2 texCoordVarying;
out vec4 outputColor;

void main(void) 
{
	outputColor = texture(tex0, texCoordVarying) * texture(texEdge, texCoordVarying);
}
