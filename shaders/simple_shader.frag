#version 450

// frag shaders need an output variable

layout(push_constant) uniform Push {
    vec2 offset;
    vec3 color;
} push;


layout (location = 0) out vec4 outColor;
// out is for output

//Fragment shader is executed once for every fragment (pixel) touched by the triangle

void main() {
                    //RGBA
    outColor = vec4(push.color, 1.0); //alpha is 1.0 (fully opaque)
}