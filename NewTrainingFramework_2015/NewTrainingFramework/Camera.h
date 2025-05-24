#pragma once
#include "../Utilities/utilities.h"

#define PI 3.14

class Camera {
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat fov;
	GLfloat nearPlane;
	GLfloat farPlane;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix perspectiveMatrix;
	
	void moveOx(int sens);
	void moveOy(int sens);
	void moveOz(int sens);
	void rotateOx(int sens);
	void rotateOy(int sens);
	void rotateOz(int sens);
	void updateAxes();
	void updateWorldView();
	void setDeltaTime(GLfloat dt);

	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up,
		GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearPlane,
		GLfloat farPlane, GLfloat fov);
};