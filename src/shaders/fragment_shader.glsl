#version 330 core

out vec4 FragColor;

in vec4 vertexColor;

uniform float greenValue;
void main() {
    vec4 greenColor = vec4(0, greenValue, 0, 1);
    FragColor = vertexColor + greenColor;
}