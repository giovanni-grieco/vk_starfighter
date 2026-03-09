#version 450

// frag shaders need an output variable

layout(push_constant) uniform Push {
    mat2 transform;
    vec2 offset;
    vec3 color;
} push;

// out is for output
layout (location = 0) out vec4 outColor;

//Fragment shader is executed once for every fragment (pixel) touched by the triangle

void main() {
    outColor = vec4(push.color, 1.0); //alpha is 1.0 (fully opaque)
}