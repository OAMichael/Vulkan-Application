#include "Camera.hpp"
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>


MyVulkanApp::Camera::Camera() {};

MyVulkanApp::Camera::Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& u, const glm::vec3& r) { 
	position  = pos;
	direction = dir;
	up = u;
	right = r;
	std::cout << *this << std::endl;
};

glm::vec3 MyVulkanApp::Camera::getPosition() const    { return position;  };
void MyVulkanApp::Camera::setPosition(const glm::vec3& pos)  { position = pos;   };

glm::vec3 MyVulkanApp::Camera::getDirection() const   { return direction; };
void MyVulkanApp::Camera::setDirection(const glm::vec3& dir) { direction = dir;  };

glm::vec3 MyVulkanApp::Camera::getRight() const       { return right; };
void MyVulkanApp::Camera::setRight(const glm::vec3& r) { right = r; };

glm::vec3 MyVulkanApp::Camera::getUp() const { return up; };
void MyVulkanApp::Camera::setUp(const glm::vec3& u) { up = u; };

float MyVulkanApp::Camera::getFov() const { return fov; };
void MyVulkanApp::Camera::setFov(const float& f) { fov = f; };

void MyVulkanApp::Camera::setDirSpeed(const float& new_speed) { dir_speed = new_speed; };
void MyVulkanApp::Camera::setRightSpeed(const float& new_speed) { right_speed = new_speed; };


void MyVulkanApp::Camera::setYaw(const float& yaw) { Yaw = yaw; };
void MyVulkanApp::Camera::setPitch(const float& pitch) { Pitch = pitch; };

void MyVulkanApp::Camera::moveX(const float& dx) { position.x += dx; };
void MyVulkanApp::Camera::moveY(const float& dy) { position.y += dy; };
void MyVulkanApp::Camera::moveZ(const float& dz) { position.z += dz; };
void MyVulkanApp::Camera::moveFront(const float& delta) { position -= direction * delta * dir_speed; };
void MyVulkanApp::Camera::moveRight(const float& delta) { position -= right * delta * right_speed; };

glm::mat4 MyVulkanApp::Camera::getMatrixView() {
	return glm::lookAt(position, position + direction, up);
};

void MyVulkanApp::Camera::updateVectors() {
	glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direction = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(direction, glm::vec3(0.0, 1.0, 0.0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, direction));
}


std::ostream& MyVulkanApp::operator<<(std::ostream& os, const Camera& camera) {
	glm::vec3 position  = camera.getPosition();
	glm::vec3 direction = camera.getDirection();
	glm::vec3 right 	= camera.getRight();
	glm::vec3 up 		= camera.getUp();
	os << "Position = ("  << position.x  << ", " << position.y  << ", " << position.z  << ");   " << 
          "Direction = (" << direction.x << ", " << direction.y << ", " << direction.z << ");   " <<
          "Right = ("     << right.x     << ", " << right.y     << ", " << right.z     << ");   " <<
          "Up = ("        << up.x        << ", " << up.y        << ", " << up.z        << ")";

    return os;
}