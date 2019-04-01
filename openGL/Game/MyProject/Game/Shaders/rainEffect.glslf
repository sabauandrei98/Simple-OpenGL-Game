#version 150

uniform float u_time;
out vec4 fragColor;
uniform vec4 myCol;

float random (in float x) {
return fract(sin(x)*1e4);
}

float random (in vec2 st) {
return fract(sin(dot(st.xy, vec2(0.750,0.350)))* 4000008.5453123);
}

float pattern(vec2 st, vec2 v, float t) {
vec2 p = floor(st+v);
return step(t, random(100.+p*.000001)+random(p.x)*0.5 );
}

void main() {
vec2 u_mouse = vec2(92.5,92.5);
vec2 res = vec2(100.,100.);
vec2 st = gl_FragCoord.xy/res;
st.x *= res.x/res.y;

vec2 grid = vec2(170.0,150.);
st *= grid;

vec2 ipos = floor(st);  // integer
vec2 fpos = fract(st);  // fraction

vec2 vel = vec2(u_time*2.*max(grid.x,grid.y)); // time
vel *= vec2(1,.0) * random(1.0+ipos.x); // direction

// Assign a random value base on the integer coord
vec2 offset = vec2(0.1,0.);


vec3 color = vec3(0.0);
color.r = pattern(st+offset,vel,0.5+u_mouse.x/res.x);
color.g = pattern(st,vel,0.5+u_mouse.x/res.x);
color.b = pattern(st-offset,vel,0.5+u_mouse.x/res.x);

// Margins
color *= step(0.1,fpos.x);

fragColor = vec4(color,0.5) * myCol;
}
