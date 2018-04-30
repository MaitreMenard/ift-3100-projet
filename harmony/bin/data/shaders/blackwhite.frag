#version 150

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
	float color ;
	color = 0.0;
	color += texture(tex0, texCoordVarying).r;
	color += texture(tex0, texCoordVarying).g;
	color += texture(tex0, texCoordVarying).b;
	color /= 3.0;
	if(color > 0.5){
		color = 1.0;
	}
	else{
		color = 0.0;
	}
    outputColor = vec4(color, color, color, texture(tex0, texCoordVarying).a);
}