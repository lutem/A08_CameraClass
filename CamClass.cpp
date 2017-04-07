#pragma once

#include <glew\glew.h>
#include "glfw\glfw3.h"
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <glm/gtx/quaternion.hpp>

using namespace glm;

class CameraClass
{
public:

	// vectors and mat4s
	vec3 camPos;
	vec3 up;
	vec3 targetPos;
	mat4 viewMat;
	mat4 projMat;

	// constructor
	CameraClass() {
		camPos = vec3(0.0f, 0.0f, 0.0f);
		up = vec3(0.0f, 1.0f, 0.0f);
		targetPos = vec3(1.0f, 0.0f, 0.0f);
		viewMat = mat4();
		projMat = perspective(45.0f, 500.0f / 500.0f, 0.01f, 100.0f);
	}

	// destructor
	~CameraClass() {
	}

	// returns view matrix
	mat4 getViewMat() {
		return viewMat;
	}
	// get projection matrices
	mat4 getProjMat(bool bOrtho) {
		if (bOrtho) {
			return projMat;
		}
		else {
			return projMat;
		}
	}
	
	// set camera position
	void SetPosition(vec3 newPos) {
		camPos = newPos;
		viewMat = lookAt(camPos, targetPos, up);
	}
	// set what camera is pointing at
	void SetTarget(vec3 targPos) {
		targetPos = targPos;
		viewMat = lookAt(camPos, targetPos, up);
	}
	// set up vector
	void SetUp(vec3 v3Up) {
		up = v3Up;
		viewMat = lookAt(camPos, targetPos, up);
	}

	// movement functions
	void MoveForwBack(float dist) {
		camPos += ((camPos - targetPos) * dist);
		targetPos += ((camPos - targetPos) * dist);
		viewMat = lookAt(camPos, targetPos, up);
	}
	void MoveUpDown(float dist) {
		camPos += (up * dist);
		targetPos += (up * dist);
		viewMat = lookAt(camPos, targetPos, up);
	}
	void MoveLeftRight(float dist) {
		camPos += cross(up, (camPos - targetPos)) * dist;
		targetPos += cross(up, (camPos - targetPos)) * dist;
		viewMat = lookAt(camPos, targetPos, up);
	}

	// orientation changes
	void ChangePitch(float degree) {
		quat q1 = quat(0.0f, vec3(1.0f, 0.0f, 0.0f));
		quat q2 = quat(degree, vec3(1.0f, 0.0f, 0.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
	void ChangeYaw(float degree) {
		quat q1 = quat(0.0f, vec3(0.0f, 1.0f, 0.0f));
		quat q2 = quat(degree, vec3(0.0f, 1.0f, 0.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
	void ChangeRoll(float degree) {
		quat q1 = quat(0.0f, vec3(0.0f, 0.0f, 1.0f));
		quat q2 = quat(degree, vec3(0.0f, 0.0f, 1.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
};