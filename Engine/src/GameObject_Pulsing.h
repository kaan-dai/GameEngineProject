#include "GameObject.h"
#include "GraphicsObject.h"

namespace Azul
{
    class GameObject_Pulsing : public GameObject
    {
    public:
        GameObject_Pulsing() = delete;
        GameObject_Pulsing(const GameObject_Pulsing&) = delete;
        GameObject_Pulsing & operator =(const GameObject_Pulsing&) = delete;
        virtual ~GameObject_Pulsing() = default;

        GameObject_Pulsing(GraphicsObject *poGraphicsObject);
        GameObject_Pulsing(GraphicsObject *poGraphicsObject, float minScale, float maxScale);
        GameObject_Pulsing(GraphicsObject *poGraphicsObject, float minScale, float maxScale, float pulseSpeed);


        virtual void Update() override;

    private:
        float pulseTimer;
        float pulseSpeed;
        float minScale;
        float maxScale;
    };
}