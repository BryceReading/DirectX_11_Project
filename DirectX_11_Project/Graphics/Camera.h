#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
	Camera();
	void setProjectionValues(float fov, float aspRatio, float nearZ, float farZ);

	const XMMATRIX& getViewMatrix() const;
	const XMMATRIX& getProjectionMatrix() const;

	const XMVECTOR& getPositionVector() const;
	const XMFLOAT3& getPositionFloat3() const;
	const XMVECTOR& getRotationVector() const;
	const XMFLOAT3& getRotationFloat3() const;

	void setPosition(const XMVECTOR& pos);
	void setPosition(float x, float y, float z);
	void positionAdjust(const XMVECTOR& pos);
	void postitinAdjust(float x, float y, float z);
	void rotationSet(const XMVECTOR& rot);
	void rotationSet(float x, float y, float z);
	void rotationAdjust(const XMVECTOR& rot);
	void rotationAdjust(float x, float y, float z);

private:
	void viewMatrixUpdate();
	XMVECTOR vectorPos;
	XMVECTOR vectorRot;
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMMATRIX matrixView;
	XMMATRIX matrixProjection;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEAFULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};