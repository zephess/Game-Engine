#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 position, float aspecRatio);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void moveForward(float distance);
	void moveRight(float distance);
	void moveUp(float distance);

	void rotate(float pitch, float yaw);

	glm::vec3 getPosition() const { return position; }
	glm::vec3 getForward() const { return forward; }
	glm::vec3 getRight() const { return right; }
	glm::vec3 getUp() const { return up; }

	void lookAt(const glm::vec3& target);
	void setPosition(const glm::vec3& pos) { position = pos; }

private:
	glm::vec3 position;

	float yaw;
	float pitch;

	float aspectRatio;

	float fov;
	float nearPlane;
	float farPlane;
	
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	void updateCameraVectors();
};

