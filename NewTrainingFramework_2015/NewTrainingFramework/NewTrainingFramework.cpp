#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"

float totalTime = 0.0f;

Camera camera(
	Vector3(0, 0, -1), // position
	Vector3(0, 0, 0),  // target
	Vector3(0, 1, 0),  // up
	PI/4,            // fov
	0.2f,             // nearPlane
	10.0f,            // farPlane
	1.0f,             // moveSpeed
	1.0f              // rotateSpeed
);

float angle = 0.0f;
float step = 0.1f;

GLuint vboId;
Shaders myShaders;

int Init(ESContext* esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//triangle data (heap)
	Vertex verticesData[6];

	// Poziții
	verticesData[0].pos = Vector3(-0.5f, 0.5f, 0.0f); // top-left
	verticesData[1].pos = Vector3(-0.5f, -0.5f, 0.0f); // bottom-left
	verticesData[2].pos = Vector3(0.5f, 0.5f, 0.0f); // top-right

	verticesData[3].pos = Vector3(0.5f, 0.5f, 0.0f); // top-right
	verticesData[4].pos = Vector3(-0.5f, -0.5f, 0.0f); // bottom-left
	verticesData[5].pos = Vector3(0.5f, -0.5f, 0.0f); // bottom-right

	// Culori
	verticesData[0].color = Vector3(0.4f, 0.0f, 0.75f);
	verticesData[1].color = Vector3(1.0f, 0.7f, 0.75f);
	verticesData[2].color = Vector3(1.0f, 0.0f, 1.0f);

	verticesData[3].color = Vector3(1.0f, 0.0f, 1.0f); 
	verticesData[4].color = Vector3(1.0f, 0.7f, 0.75f);
	verticesData[5].color = Vector3(1.0f, 1.0f, 1.0f);

	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);


	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	Matrix modelMatrix;
	modelMatrix.SetRotationZ(angle); // sau SetIdentity() pentru test
	//modelMatrix.SetIdentity();

	//Matrix MVP = camera.viewMatrix; 
	//Matrix MVP = camera.worldMatrix;
	//Matrix MVP = camera.viewMatrix * camera.perspectiveMatrix; 
	Matrix MVP = modelMatrix * camera.viewMatrix * camera.perspectiveMatrix; //M * V * P

	if (myShaders.mvpUniform != -1)
	{
		glUniformMatrix4fv(myShaders.mvpUniform, 1, GL_FALSE, &MVP.m[0][0]);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= Globals::frameTime) {
		//camera.setDeltaTime(Globals::frameTime);
		camera.deltaTime = Globals::frameTime;
		//angle += step;
		//if (angle > 2.0f * PI)
		//	angle -= 2.0f * PI;
		totalTime -= Globals::frameTime;
	}

}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	/*
	if (bIsPressed) 
	{
		printf("Tasta apasata %c (ASCII: %d)\n", key, (int)key);
	}*/
	if (bIsPressed)
		switch (key) {
		case 'w': case 'W':
			camera.moveOz(-1);
			break;
		case 'a': case 'A':
			camera.moveOx(-1);
			break;
		case 's': case 'S':
			camera.moveOz(1);
			break;
		case 'd': case 'D':
			camera.moveOx(1);
			break;
		case 'q': case 'Q':
			camera.moveOy(-1);
			break;
		case 'e': case 'E':
			camera.moveOy(1);
			break;

		case VK_UP:
			camera.rotateOx(-1);
			break;
		case VK_DOWN:
			camera.rotateOx(1);
			break;
		case VK_LEFT:
			camera.rotateOy(-1);
			break;
		case VK_RIGHT:
			camera.rotateOy(1);
			break;
		case 'g': case 'G':
			camera.rotateOz(1);
			break;
		case 'h': case 'H':
			camera.rotateOz(-1);
			break;
		}


}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;
	
	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();


	return 0;
}