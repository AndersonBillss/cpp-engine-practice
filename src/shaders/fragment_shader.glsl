#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    vec4 mixedColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.7);
    FragColor = mixedColor * vec4(ourColor, 1.0);
}