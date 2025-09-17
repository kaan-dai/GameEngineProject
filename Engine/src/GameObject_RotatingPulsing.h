#include "GameObject.h"
#include "GraphicsObject.h"

namespace Azul
{
    class GameObject_RotatingPulsing : public GameObject
    {
    public:
        GameObject_RotatingPulsing() = delete;
        GameObject_RotatingPulsing(const GameObject_RotatingPulsing&) = delete;
        GameObject_RotatingPulsing & operator =(const GameObject_RotatingPulsing&) = delete;
        virtual ~GameObject_RotatingPulsing() = default;

        GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject);
        GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis);
        GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis, float rotSpeed);
        GameObject_RotatingPulsing(GraphicsObject* poGraphicsObject, Rot1 axis, float rotSpeed, float minScale, float maxScale);
        GameObject_RotatingPulsing(GraphicsObject *poGraphicsObject, Rot1 axis, float rotSpeed, float minScale, float maxScale, float pulseSpeed);

        virtual void Update() override;

    private:
        float angle;
        float rotSpeed;
        Rot1 rotAxis;
        float pulseTimer;
        float pulseSpeed;
        float minScale;
        float maxScale;
    };
}