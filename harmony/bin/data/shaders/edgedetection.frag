#version 150

uniform sampler2DRect tex0;
uniform float blurAmnt;

in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	if(texCoordVarying.x > 1 && texCoordVarying.x < 1023 && texCoordVarying.y > 1 && texCoordVarying.y < 767){
		color += 8.0 * texture2D(tex0, texCoordVarying);
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(1.0, 0.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(1.0, 1.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(1.0, -1.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(-1.0, 0.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(-1.0, 1.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(-1.0, -1.0));
		
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(0.0, 1.0));
		color += (-1.0) * texture2D(tex0, texCoordVarying + vec2(0.0, -1.0));
	}
   
    outputColor = vec4(color.r, color.g, color.d, texture2D(tex0, texCoordVarying).a);
}
