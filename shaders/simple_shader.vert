#version 450

//executed once for every vertex

// 0,0 Center

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;


layout(push_constant) uniform Push {
    vec2 offset;
    vec3 color;
} push;
//locations of input and output is different

void main() {
    gl_Position = vec4(position + push.offset, 0.0, 1.0);
}