#include "Camera.h"

Camera::Camera()
	: position(Vector3(0, 0, -1)),
	target(Vector3(0, 0, 0)),
	up(Vector3(0, 1, 0)),
	fov(45.0f),
	nearPlane(0.2f),
	farPlane(10.0f),
	moveSpeed(0.1f),
	rotateSpeed(0.1f)
{};

Camera::Camera(Vector3 position, Vector3 target, Vector3 up,
	GLfloat fov, GLfloat nearPlane, GLfloat farPlane,
	GLfloat moveSpeed, GLfloat rotateSpeed)
	: position(position),
	target(target), up(up),
	fov(fov), nearPlane(nearPlane),
	farPlane(farPlane), moveSpeed(moveSpeed),
	rotateSpeed(rotateSpeed)
{};

void Camera::moveOx(int sens) {
	Vector3 forward;
	Vector3 vectorDeplasare;
	forward = xAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
}