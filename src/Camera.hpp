#pragma once

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>


namespace MyVulkanApp {

	class Camera 
	{	
	private:
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 right;
		glm::vec3 up;

		float dir_speed = 1.0f;
		float right_speed = 1.0f;

		float Yaw = 90.0f;
		float Pitch = 0.0f;
		float fov = 90.0f;

	public:
		Camera();
		Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& u, const glm::vec3& r);
		~Camera() = default;

		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3& pos);

		glm::vec3 getDirection() const;
		void setDirection(const glm::vec3& dir);
		
		glm::vec3 getRight() const;
		void setRight(const glm::vec3& r);
		
		glm::vec3 getUp() const;
		void setUp(const glm::vec3& u);
		
		float getFov() const;
		void setFov(const float& f);

		void setDirSpeed(const float& new_speed);
		void setRightSpeed(const float& new_speed);


		void setYaw(const float& yaw);
		void setPitch(const float& pitch);
		
		void moveX(const float& dx);
		void moveY(const float& dy);
		void moveZ(const float& dz);
		void moveFront(const float& delta);
		void moveRight(const float& delta);
		
		glm::mat4 getMatrixView();
		
		void updateVectors();
	};

	std::ostream& operator<<(std::ostream& os, const Camera& camera);
}