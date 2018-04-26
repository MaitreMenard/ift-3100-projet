#version 330

in vec2 varyingtexcoord;

out vec4 fragColor;

uniform sampler2D texColor;
uniform sampler2D texBumpMap;

void main(void) {
    
    vec4 colorMap = texture(texColor, varyingtexcoord);
    fragColor = colorMap;
    
}