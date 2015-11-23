#version 430
uniform sampler2D srcTex;
in vec2 texCoord;
out vec4 color;
void main() {
// gl_FragColor = texture(srcTex, texCoord);
color = texture(srcTex, texCoord);
color = vec4(1,0,0,1);
}