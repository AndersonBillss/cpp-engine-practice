#include "../math.hpp"

class Camera
{
public:
    float pitch = 0;
    float yaw = -90.0f;
    Math::Vec3 position;
    Camera()
    {
        position.x = 0;
        position.y = 0;
        position.z = 0;
    }

    Math::Mat4 getView();

    Math::Vec3 getFront();
    Math::Vec3 getUp();
};