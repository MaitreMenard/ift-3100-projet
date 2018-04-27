// IFT3100H18 ~ color_fill_120_fs.glsl

#version 120

// couleur de remplissage du matériau
uniform vec3 color;

void main()
{
  // déterminer la couleur du fragment
  gl_FragColor = vec4(color, 1.0);
}
