#version 330 core
out vec4 FragColor;  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float logoOpacity;

void main(){
    vec4 mixedColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), logoOpacity);
    FragColor = mixedColor;
}