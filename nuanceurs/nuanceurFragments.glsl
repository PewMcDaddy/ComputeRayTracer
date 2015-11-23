#version 430
uniform sampler2D srcTex;
in vec2 texCoord;
out vec4 color;
void main() {
// gl_FragColor = texture(srcTex, texCoord);
	//color = vec4(cos(texCoord.x), sin(texCoord.y), 0.5,1);
	color = texture(srcTex, texCoord);
}