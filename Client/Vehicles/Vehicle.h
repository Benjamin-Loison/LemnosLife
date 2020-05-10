#ifndef DEF_VEHICLE
#define DEF_VEHICLE

#include "../LemnosLife/Map/User/ViewGravity.h"
#include "../LemnosLife/Render/Shader.h"
#include "../2D/vector2d.h"
#include <string>
#include "gl.h"

class Vehicle
{
    public:
        Vehicle();
        Vehicle(std::string, ViewGravity, std::string);
        void initializeRender(), render(), initializeVehicle(), initializeTexture(), initializeVehicles();
    private:
        std::string m_name, m_camouflage;
        bool m_siren, m_isABoat, m_needInit, m_refreshSkinFinished;
        unsigned int m_VBO, m_VAO, texNumber, verticesNumber;
        ViewGravity m_viewGravity;
        GLuint m_texture;
        Shader shader;
        point m_collisions[4];
        Position m_lastPosition;
        double m_lastAngle;
};

void addVehicle(std::string, ViewGravity, std::string = ""), renderVehicles(), initializeVehicles();
glm::vec3 getVec3(Vector3D);

#endif
