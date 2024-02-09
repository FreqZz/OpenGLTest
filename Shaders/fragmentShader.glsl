#version 330 core

in vec3 myColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D myTexture;

void main() {
    FragColor = texture(myTexture, TexCoord);
}