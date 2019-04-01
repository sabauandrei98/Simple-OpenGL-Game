#version 150

uniform vec4 myColor;
uniform sampler2D myTexture;
uniform float uvX;
uniform float uvY;

uniform float lightAttenuation;
uniform float lightIntensity;
uniform vec4 lightColor;

in vec2 uv;
out vec4 fragColor;

void main()
{
float p = lightAttenuation;
float q = lightIntensity;
fragColor = myColor * lightColor * texture(myTexture,fract(vec2(uv.x + uvX, uv.y + uvY)));
}
