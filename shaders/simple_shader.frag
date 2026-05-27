#version 450

layout(location = 0) in vec3 fragColor; //from vertex shader
layout(location = 1) in vec3 fragPosWorld; //from vertex shader
layout(location = 2) in vec3 fragNormalWorld; //from vertex shader

layout(location = 0) out vec4 outColor;

struct PointLight {
    vec4 position; //ignore w
    vec4 color; // w is intensity
};

layout(set=0, binding=0) uniform GlobalUbo{
    mat4 projection;
    mat4 view;
    mat4 inverseView;
    vec4 ambientLightColor; //w is intensity
    PointLight pointLights[10];
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    mat4 model;
    mat4 normal;
} push;

void main() {

    vec3 diffuseLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
    vec3 surfaceNormal = normalize(fragNormalWorld);

    vec3 specularLight = vec3(0.0);

    vec3 cameraPosWorld = ubo.inverseView[3].xyz;
    vec3 viewDirection = normalize(cameraPosWorld - fragPosWorld); //from fragment to camera

    for (int i = 0; i<ubo.numLights; i++){
        PointLight light = ubo.pointLights[i];
        vec3 directionToLight = light.position.xyz - fragPosWorld; //from fragment to lightPoint
        float attenuation = 1.0 / dot(directionToLight, directionToLight); // squared
        
        directionToLight = normalize(directionToLight);
        
        float cosAngIncidence = max(dot(surfaceNormal, directionToLight), 0);
        vec3 intensity = light.color.xyz * light.color.w * attenuation;

        diffuseLight += intensity * cosAngIncidence;

        vec3 halfAngle = normalize(directionToLight + viewDirection);
        float blinnTerm = dot(halfAngle, surfaceNormal);
        blinnTerm = clamp(blinnTerm, 0, 1);
        blinnTerm = pow(blinnTerm, 32.0);
        specularLight += light.color.xyz * blinnTerm * attenuation;
    }

    outColor = vec4(diffuseLight * fragColor + specularLight * fragColor, 1.0);
}