#version 150

uniform vec4 myColor;
uniform sampler2D myTexture;
uniform float uvX;
uniform float uvY;

in vec2 uv;
out vec4 fragColor;
in vec3 pos;
uniform float lightAttenuation;
uniform float lightIntensity;
uniform vec4 lightColor;

void main()
{
vec4 col = myColor;
float q = lightAttenuation;

vec3 a = vec3(0,0,0);
vec3 b = pos;
b.y = 0;

float intensity = lightIntensity;
float distance = length(a - b);
float attenuation = 1 / distance * intensity * 10 ;
vec4 color = vec4(attenuation , attenuation , attenuation , 1) * lightColor;

fragColor = color * texture(myTexture,fract(vec2(uv.x + uvX, uv.y + uvY)));
}
