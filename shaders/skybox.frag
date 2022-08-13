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

// Final frag color
layout(location = 0) out vec4 outColor;

// Skybox
layout(location = 0) in vec3 CubeMapFragTexCoord;
layout(binding = 2) uniform samplerCube CubeTexSampler;


void main(void) {

    outColor = texture(CubeTexSampler, CubeMapFragTexCoord);
}