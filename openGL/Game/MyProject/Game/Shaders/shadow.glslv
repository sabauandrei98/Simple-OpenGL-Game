uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 myTransform;

layout(location = POSITION) in vec3 position;
layout(location = TEXCOORD0) in vec2 texCoord;

out vec2 uv;

void main()
{
uv = texCoord.xy;

gl_Position = IvModelViewProjectionMatrix * myTransform * vec4(position,1.0);

}
