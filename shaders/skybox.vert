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


// Skybox
layout(location = 0) in vec3 CubeMapInPosition;
layout(location = 1) in vec3 CubeMapInColor;
layout(location = 2) in vec3 CubeMapInTexCoord;

layout(location = 0) out vec3 CubeMapFragTexCoord;


void main(void) {
    
    CubeMapFragTexCoord = CubeMapInTexCoord;
    gl_Position = ubo.proj * mat4(mat3(ubo.view)) * ubo.model * vec4(CubeMapInPosition, 1.0);
}