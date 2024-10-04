#version 330

uniform vec4 palette[256];
uniform float time;

in vec2 pos;
in vec2 vel;
in int typ;

out vec4 vColor;
out vec2 texCoord;

void main(void) {
    vColor = palette[uint(typ)];
    texCoord = pos;
    gl_Position = vec4(pos,0.0,1.0);
}
