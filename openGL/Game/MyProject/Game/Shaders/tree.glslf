#version 150

uniform vec4 myColor;
uniform sampler2D myTexture;
uniform float uvX;
uniform float uvY;

in vec2 uv;
out vec4 fragColor;

uniform float lightAttenuation;
uniform float lightIntensity;
uniform vec4 lightColor;

void main()
{
float q = lightIntensity;
vec4 color = vec4(1.03 - lightAttenuation, 1.03 - lightAttenuation , 1.03 - lightAttenuation , 1) * myColor * lightColor;
fragColor = color * texture(myTexture,fract(vec2(uv.x + uvX, uv.y + uvY)));
}
