#include "GameObject_Pulsing.h"
#include "MathEngine.h"

namespace Azul
{
    GameObject_Pulsing::GameObject_Pulsing(GraphicsObject *poGraphicsObject)
        : GameObject(poGraphicsObject),
        pulseTimer(0.0f),
        pulseSpeed(0.05f),
        minScale(0.5f),
        maxScale(1.0f)
    {

    }

    GameObject_Pulsing::GameObject_Pulsing(GraphicsObject *poGraphicsObject, float _minScale, float _maxScale)
        : GameObject(poGraphicsObject),
        pulseTimer(0.0f),
        pulseSpeed(0.05f),  
        minScale(_minScale),
        maxScale(_maxScale)
    {

    }

    GameObject_Pulsing::GameObject_Pulsing(GraphicsObject *poGraphicsObject, float _minScale, float _maxScale, float pulseSpeed)
        : GameObject(poGraphicsObject),
        pulseTimer(0.0f),
        pulseSpeed(pulseSpeed),
        minScale(_minScale),
        maxScale(_maxScale)
    {

    }

    void GameObject_Pulsing::Update()
    {
        pulseTimer += pulseSpeed;

        float normSin= (Trig::sin(pulseTimer) + 1.0f) * 0.5f; 
        float currentScale = minScale + (maxScale - minScale) * normSin;
        this->SetScale(currentScale);

        GameObject::Update();
    }
}