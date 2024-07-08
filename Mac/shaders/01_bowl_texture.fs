
#version 330 core
precision mediump float;
out vec4 color;
uniform sampler2D uTexture;
in vec2 vTexcoord;

void main()
{
  color.a = 1.0;
  color.rgb = texture(uTexture, vTexcoord).rgb;

  //color.rgb = vec3(0.0,1.0,0.0);
}
