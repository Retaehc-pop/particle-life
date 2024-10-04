#version 330 core

in vec4 fColor;
in vec2 texCoord;  // normalized [-1, 1]
out vec4 FragColor;

void main(void) {
    if (length(texCoord) > 1.0) discard;  // Discard fragments outside the circle radius

    FragColor = fColor;  // Draw the circle with the assigned color
}

