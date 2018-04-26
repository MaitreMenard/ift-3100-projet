#version 330	

uniform sampler2DRect tex0;

in vec2 texCoordVarying;
out vec4 outputColor;

void main(void) 
{
		bool isEdge = false;
		
		if(texture(tex0, texCoordVarying + vec2(1.0, 0.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(0.0, 1.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(-1.0, 0.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(0.0, -1.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(1.0, 1.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(-1.0, -1.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(-1.0, 1.0)).r == 0.0)
			isEdge = true;
		if(texture(tex0, texCoordVarying + vec2(-1.0, -1.0)).r == 0.0)
			isEdge = true;
		
		if(isEdge)
			outputColor = vec4(0.0, 0.0, 0.0, 1.0);
		else
			outputColor = texture(tex0, texCoordVarying);
}
