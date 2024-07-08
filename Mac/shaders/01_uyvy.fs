#version 330 core
out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D texUYVY422;

const lowp vec3 offset = vec3(-0.0625, -0.5, -0.5);
	
const mediump mat3 converter = mat3(
	1.164, 1.164, 1.164,
	0.000,-0.391, 2.018,
	1.596,-0.813, 0.000
);

void main(void)
{
	vec3 yuvColor;
	ivec2  TexSize = textureSize(texUYVY422, 0);//纹理图片大小
	int texCoordX = int(vTexCoord.x*TexSize.x * 2);
    if (mod(texCoordX, 2.0) == 1.0)
	    yuvColor.x = texture(texUYVY422, vTexCoord).w;
	else
	    yuvColor.x = texture(texUYVY422, vTexCoord).y;

    yuvColor.y = texture(texUYVY422, vTexCoord).x; // color u
	yuvColor.z = texture(texUYVY422, vTexCoord).z; // color v
 
	vec3 rgbColor;
	yuvColor += offset;
	rgbColor = converter * yuvColor;
 
	FragColor = vec4(rgbColor, 1.0f);
}
