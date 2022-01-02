#include "Camera.h"

Camera::Camera()
{
	this->position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->vectorPos = XMLoadFloat3(&this->position);
	this->rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->vectorRot = XMLoadFloat3(&this->rotation);

	this->viewMatrixUpdate();
}

void Camera::setProjectionValues(float fov, float aspRatio, float nearZ, float farZ)
{
	float fovRads = (fov / 360.0f) * XM_2PI;
	this->matrixProjection = XMMatrixPerspectiveFovLH(fovRads, aspRatio, nearZ, farZ);
}

const XMMATRIX& Camera::getViewMatrix()const
{
	return this->matrixView;
}

const XMMATRIX& Camera::getProjectionMatrix() const
{
	return this->matrixProjection;
}

const XMVECTOR& Camera::getPositionVector() const
{
	return this->vectorPos;
}

const XMFLOAT3& Camera::getPositionFloat3() const
{
	return this->position;
}

const XMVECTOR& Camera::getRotationVector() const
{
	return this->vectorRot;
}

const XMFLOAT3& Camera::getRotationFloat3() const
{
	return this->rotation;
}

void Camera::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->position, pos);
	this->vectorPos = pos;

	this->viewMatrixUpdate();
}

void Camera::setPosition(float x, float y, float z)
{
	this->position = XMFLOAT3(x, y, z);
	this->vectorPos = XMLoadFloat3(&this->position);
	
	this->viewMatrixUpdate();
}

void Camera::positionAdjust(const XMVECTOR& position)
{
	this->vectorPos += position;
	XMStoreFloat3(&this->position, this->vectorPos);
	this->viewMatrixUpdate();
}

void Camera::postitinAdjust(float x, float y, float z)
{
	this->position.x += x;
	this->position.y += y;
	this->position.z += z;
	this->vectorPos = XMLoadFloat3(&this->position);
	this->viewMatrixUpdate();
}

void Camera::rotationSet(const XMVECTOR& rot)
{
	this->vectorRot = rot;
	XMStoreFloat3(&this->rotation, rot);
	this->viewMatrixUpdate();
}

void Camera::rotationSet(float x, float y, float z)
{
	this->rotation = XMFLOAT3(x, y, z);
	this->vectorRot = XMLoadFloat3(&this->rotation);
	this->viewMatrixUpdate();
}

void Camera::rotationAdjust(const XMVECTOR& rot)
{
	this->vectorRot += rot;
	XMStoreFloat3(&this->rotation, this->vectorRot);
	this->viewMatrixUpdate();
}

void Camera::rotationAdjust(float x, float y, float z)
{
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
	this->vectorRot = XMLoadFloat3(&this->rotation);
	this->viewMatrixUpdate();
}

void Camera::viewMatrixUpdate() // This updates the view matrix and also the movement vectors
{
	// Camera rotation matrix calculation
	XMMATRIX rotationCamMatrix = XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z);
	// Unit vector of cam target based off camera forward values transformed by cam rotation 
	XMVECTOR targetCam = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, rotationCamMatrix);
	// Adjust cam target to be offset by the cameras current position
	targetCam += this->vectorPos;
	// Up direction calculated based on current rotation
	XMVECTOR dirUp = XMVector3TransformCoord(this->DEAFULT_UP_VECTOR, rotationCamMatrix);
	// View Matrix re-built
	this->matrixView = XMMatrixLookAtLH(this->vectorPos, targetCam, dirUp);
}