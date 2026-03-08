#version 450

// frag shaders need an output variable

//using location 0, there can be more
layout (location = 0) in vec3 fragColor; // input from vertex shader

layout (location = 0) out vec4 outColor;
// out is for output

//Fragment shader is executed once for every fragment (pixel) touched by the triangle

void main() {
                    //RGBA
    outColor = vec4(fragColor, 1.0); //alpha is 1.0 (fully opaque)
}