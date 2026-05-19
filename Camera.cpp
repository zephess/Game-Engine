#include "Camera.h"

Camera::Camera(glm::vec3 position, float aspecRatio) : position(position), aspectRatio(aspecRatio), 
	yaw(-90.0f), pitch(0.0f), fov(60.0f), nearPlane(0.1f), farPlane(100.0f)
{
	// Initialize camera vectors
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// Calculate the new forward vector
	glm::vec3 front;
	// Convert yaw and pitch from degrees to radians for trigonometric functions
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::getViewMatrix() const
{
	// Create view matrix using glm::lookAt
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	// Create projection matrix using glm::perspective
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::moveForward(float distance)
{
	// Move camera along the forward vector
	position += forward * distance;
}
void Camera::moveRight(float distance)
{
	// Move camera along the right vector
	position += right * distance;
}
void Camera::moveUp(float distance)
{
	// Move camera along the up vector
	position += up * distance;
}

void Camera::rotate(float pitchOffset, float yawOffset)
{
	// Update pitch and yaw angles
	pitch += pitchOffset;
	yaw += yawOffset;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);
	updateCameraVectors();
}

void Camera::lookAt(const glm::vec3& target)
{
	// Update camera orientation to look at target point
	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
	pitch = glm::degrees(asin(forward.y));
	yaw = glm::degrees(atan2(forward.z, forward.x));
}