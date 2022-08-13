#version 450
#extension GL_ARB_separate_shader_objects : enable

//#define POINT_LIGHT


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

// Background
layout(location = 0) in vec3 backColor;

// Model
layout(location = 1) in vec2 fragTexCoord;
layout(binding = 1) uniform sampler2D texSampler;


const float INFINITY = 1e10;
const vec3 light_dir = normalize(vec3(0, 1, 0));
vec3 light_pos = 250 * vec3(0, sin(ubo.time), cos(ubo.time));
mat4 full = ubo.proj * ubo.view * ubo.model;
vec3 texcolor = texture(texSampler, fragTexCoord).xyz;


struct Ray {
    vec3 origin;
    vec3 direction;
};


struct Sphere {
    vec3 center;
    float radius;
    vec3 color;
    bool diffuse;
    bool emitter;
};


struct IntersectInfo {
    bool result;
    float t;
};


IntersectInfo SpheresIntersect(Ray ray, Sphere sphere) {
    IntersectInfo result = {false, INFINITY};

    vec3 x = ray.origin - sphere.center;
    float x_times_dir = dot(x, ray.direction);
    if(x_times_dir > 0) {
        return result;
    }

    float D = x_times_dir * x_times_dir - dot(x, x) + sphere.radius * sphere.radius;
    if(D < 0) {
        return result;
    }

    float sqrtD = sqrt(D);
    float t0 = -x_times_dir - sqrtD;
    float t1 = -x_times_dir + sqrtD;
    
    if(t0 < 0 && t1 > 0)
        t0 = t1;

    if(t0 > 0 && t0 < INFINITY) {
        result.result = true;
        result.t = t0;
    }

    return result;
}


vec3 RayTrace(Ray ray, Sphere[1] spheres) {
    vec3 color = texcolor;
    Sphere near_sphere;
    bool HasIntersect = false;
    float t_near = INFINITY;
    IntersectInfo result;

    for(int i = 0; i < spheres.length(); i++) {
        result = SpheresIntersect(ray, spheres[i]);
        if(result.result) {
            HasIntersect = true;
            if(result.t < t_near) {
                t_near = result.t;
                near_sphere = spheres[i];
            }
        }
    }
    if(HasIntersect) {
        if(t_near * dot(ray.direction, ubo.camera_dir) > float(gl_FragCoord.z) / gl_FragCoord.w)
            return color;

        if(near_sphere.emitter)
            return near_sphere.color;


        vec3 pHit = ray.origin + t_near * ray.direction;
        

        Ray ShadowRay;
        ShadowRay.origin = pHit;

        #ifdef POINT_LIGHT
        ShadowRay.direction = normalize(light_pos - pHit);
        #else
        ShadowRay.direction = light_dir;
        #endif

        for(int j = 0; j < spheres.length(); j++) {
            result = SpheresIntersect(ShadowRay, spheres[j]);
            if(!spheres[j].emitter && result.result) {
                color = vec3(0.0, 0.0, 0.0);
                return color;
            }
        }

        vec3 nHit = normalize(pHit - near_sphere.center);

        float intense = dot(nHit, ShadowRay.direction);
        if(intense < 0)
            color = vec3(0.0, 0.0, 0.0);
        else
            color = near_sphere.color * intense + 0.001;
    }
    return color;
}


void main(void) {

    const float Aspect = ubo.WIDTH / float(ubo.HEIGHT);
    const float angle = tan(3.14159 / 180.0 * ubo.fov * 0.5);

    float i = ((gl_FragCoord.x + 0.5) / ubo.WIDTH  - 0.5) * angle * Aspect;
    float j = ((gl_FragCoord.y + 0.5) / ubo.HEIGHT - 0.5) * angle;

    Ray ray;
    ray.origin = ubo.camera_pos;

    vec3 right = normalize(cross(ubo.camera_dir, vec3(0.0, 1.0, 0.0)));

    ray.direction = normalize(2 * i * right - 2 * j * ubo.camera_up + ubo.camera_dir);
    Sphere spheres[1];
    spheres[0].center = vec3(-3.48844, 2.34008, 3.45917);
    spheres[0].radius = 0.4;
    spheres[0].color = vec3(0.0, 1.0, 0.0);
    spheres[0].diffuse = true;
    spheres[0].emitter = false;
    
    outColor = vec4(RayTrace(ray, spheres), 1);
}