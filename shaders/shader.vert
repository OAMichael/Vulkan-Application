#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;

    vec3 camera_pos;
    vec3 camera_dir;
    vec3 camera_up;

    int WIDTH;
    int HEIGHT;
    float time;
    float fov;
} ubo;

// Background
layout(location = 0) out vec3 backColor;

// Model 
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 1) out vec2 fragTexCoord;


void main(void) {
    backColor = inColor;
    fragTexCoord = inTexCoord;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
}