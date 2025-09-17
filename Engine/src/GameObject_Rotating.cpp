#include "MathEngine.h"
#include "GameObject_Rotating.h"

namespace Azul
{
    GameObject_Rotating::GameObject_Rotating(GraphicsObject *poGraphicsObject)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(0.01f),
        rotAxis(Rot1::Z)
    {
    }

    GameObject_Rotating::GameObject_Rotating(GraphicsObject *poGraphicsObject, Rot1 axis)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(0.01f),
        rotAxis(axis)
    {
    }

    GameObject_Rotating::GameObject_Rotating(GraphicsObject *poGraphicsObject, Rot1 axis, float _rotSpeed)
        : GameObject(poGraphicsObject),
        angle(0.0f),
        rotSpeed(_rotSpeed),
        rotAxis(axis)
    {
    }

    void GameObject_Rotating::Update()
    {
        angle += rotSpeed;
        Trans TransA(this->poPos->x(), this->poPos->y(), this->poPos->z());
        Scale ScaleA(this->scale, this->scale, this->scale);
        Rot RotA(rotAxis, angle);

        Mat4 *world = this->GetWorld();
        *world = ScaleA * RotA * TransA;

        this->poGraphicsObject->SetWorld(*world);
    }
}