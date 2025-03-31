#include "Camera.h"

#include "Engine/Renderer/IRenderer.h"
#include "Utility/Matrix/Matrix4.h"
#include "Engine/Log.h"

void Camera::Update()
{
	Actor::Update();

	Vector3 camPosition = mTransform->mPosition;
	Vector3 target = mTransform->mPosition + mTransform->Forward() * 100.0f;
	Vector3 up = Vector3::Up;

	//Log::Info("" + std::to_string(camPosition.x) + ", " + std::to_string(camPosition.y) + ", " + std::to_string(camPosition.z));

	Matrix4 view = Matrix4::CreateLookAt(camPosition, target, up);
	mScene->GetRenderer()->SetViewMatrix(view);
}
