#include "GameObject_RotatingPulsing.h"
#include "MathEngine.h"

namespace Azul
{
    GameObject_RotatingPulsing::GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(0.01f),
        rotAxis(Rot1::Z),
        pulseTimer(0.0f),
        minScale(0.5f),
        maxScale(1.0f),
        pulseSpeed(0.05f)     
    {

    }

    GameObject_RotatingPulsing::GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(0.01f),
        rotAxis(axis),
        pulseTimer(0.0f),
        minScale(0.5f),
        maxScale(1.0f),
        pulseSpeed(0.05f)
    {

    }

    GameObject_RotatingPulsing::GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis, float _rotSpeed)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(_rotSpeed),
        rotAxis(axis),
        pulseTimer(0.0f),
        minScale(0.5f),
        maxScale(1.0f),
        pulseSpeed(0.05f)
    {

    }

	GameObject_RotatingPulsing::GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis, float _rotSpeed, float _minScale, float _maxScale)
		: GameObject(poGraphicsObject),
		angle(0.0f),
		rotSpeed(_rotSpeed),
		rotAxis(axis),
		pulseTimer(0.0f),
        minScale(_minScale),
        maxScale(_maxScale),
		pulseSpeed(0.05f)
	{

	}

    GameObject_RotatingPulsing::GameObject_RotatingPulsing(GraphicsObject* poGraphicsObject, Rot1 axis, float _rotSpeed, float _minScale, float _maxScale, float _pulseSpeed)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(_rotSpeed),
        rotAxis(axis),
        pulseTimer(0.0f),
        minScale(_minScale),
        maxScale(_maxScale),
        pulseSpeed(_pulseSpeed)
    {

    }

    void GameObject_RotatingPulsing::Update()
    {
        angle += rotSpeed;
        pulseTimer += pulseSpeed;
        float normSin = (Trig::sin(pulseTimer) + 1.0f) * 0.5f;
        float currentScale = minScale + (maxScale - minScale) * normSin;

        Trans TransA(this->poPos->x(), this->poPos->y(), this->poPos->z());
        Scale ScaleA(currentScale, currentScale, currentScale);
        Rot RotA(rotAxis, angle);

        Mat4 *world = this->GetWorld();
        *world = ScaleA * RotA * TransA;

        this->poGraphicsObject->SetWorld(*world);
    }
}