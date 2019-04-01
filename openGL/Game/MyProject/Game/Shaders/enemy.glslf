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

//vec3 lightLocation = vec3(2,0,2);
//float distance = length(lightLocation - gl_FragCoord.xy);
//float attenuation = 1.0 / distance;
//float screenHeight = 1280;
//vec4 color = vec4(attenuation, attenuation, attenuation, pow(attenuation, 3)) * vec4(myColor.xyz, 1);

//fragColor = color;
float q = lightIntensity;
vec4 color = vec4(1.03 - lightAttenuation, 1.03 - lightAttenuation , 1.03 - lightAttenuation , 1) * myColor* lightColor;
fragColor = color * texture(myTexture,fract(vec2(uv.x + uvX, uv.y + uvY)));
}



