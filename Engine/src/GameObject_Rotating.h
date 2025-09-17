#include "GameObject.h"
#include "GraphicsObject.h"

namespace Azul
{
    class GameObject_Rotating : public GameObject
    {
    public:
        GameObject_Rotating() = delete;
        GameObject_Rotating(const GameObject_Rotating&) = delete;
        GameObject_Rotating & operator =(const GameObject_Rotating&) = delete;
        virtual ~GameObject_Rotating() = default;

        GameObject_Rotating(GraphicsObject *poGraphicsObject);
        GameObject_Rotating(GraphicsObject *poGraphicsObject, Rot1 axis);
        GameObject_Rotating(GraphicsObject *poGraphicsObject, Rot1 axis, float _rotSpeed);

        virtual void Update() override;
		 
    private:
        float angle;
        float rotSpeed;
        Rot1 rotAxis;
    };
}