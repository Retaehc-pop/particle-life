#version 330 core

uniform bool wrap;        // Whether to wrap particles at the boundaries
uniform float size;       // Size of the generated quads (particles)

layout (points) in;  // Input points from the vertex shader
layout (triangle_strip, max_vertices = 16) out;  // Output a quad (with potential wrapping)

in vec4 vColor[];  // Input color from the vertex shader
out vec4 fColor;   // Output color to the fragment shader
out vec2 texCoord; // Texture coordinates for fragment shader

#define Pi 3.14159265359

// Generate a quad around the center point (representing a particle)
void quad(vec4 center) {
    float r = 0.5 * size;  // Half the size is used for offsetting

    // Bottom-left corner
    gl_Position = center + vec4(-r, -r, 0.0, 0.0);
    texCoord = vec2(-1.0, -1.0);
    EmitVertex();

    // Bottom-right corner
    gl_Position = center + vec4(r, -r, 0.0, 0.0);
    texCoord = vec2(1.0, -1.0);
    EmitVertex();

    // Top-left corner
    gl_Position = center + vec4(-r, r, 0.0, 0.0);
    texCoord = vec2(-1.0, 1.0);
    EmitVertex();

    // Top-right corner
    gl_Position = center + vec4(r, r, 0.0, 0.0);
    texCoord = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();  // End the quad drawing
}

void main() {
    fColor = vColor[0];  // Pass the color to the fragment shader
    vec4 center = gl_in[0].gl_Position;  // The particle center in NDC

    // Wrap the particles' positions if needed (wrapping within [0, 1))
    if (wrap) {
        center.x = mod(center.x, 1.0);
        center.y = mod(center.y, 1.0);
    }

    // Draw the particle as a quad
    quad(center);

    // If wrapping is enabled, handle particles near the edges by drawing them on the opposite side
    if (wrap) {
        float r = 0.5 * size;  // Radius of the particle
        int dx = 0;
        int dy = 0;

        // Check if the particle is near the left or right edge
        if (center.x < r) {
            dx = 1;
        } else if (center.x > 1.0 - r) {
            dx = -1;
        }

        // Check if the particle is near the top or bottom edge
        if (center.y < r) {
            dy = 1;
        } else if (center.y > 1.0 - r) {
            dy = -1;
        }

        // Draw additional quads if the particle needs to appear on the other side due to wrapping
        if (dx != 0) {
            quad(center + vec4(float(dx), 0.0, 0.0, 0.0));
        }
        if (dy != 0) {
            quad(center + vec4(0.0, float(dy), 0.0, 0.0));
        }
        if ((dx != 0) && (dy != 0)) {
            quad(center + vec4(float(dx), float(dy), 0.0, 0.0));
        }
    }
}

