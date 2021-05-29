#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include "vector3d.h"
#include <map>
#include <string>
#include <SDL2/SDL.h>
//#include "../../../LemnosLife/Map/Position.h" // can't find the file lol STUPIDO !

#define DEFAULT_F5_DISTANCE 3

class FreeFlyCamera
{
    public:
        Vector3D m_position, m_target, m_cameraPosition, m_F5CameraPosition, m_F5CameraTarget, m_forward, left, forwardTmp; // should make getters and setters ?
        FreeFlyCamera(const Vector3D &position = Vector3D(0, 0, 0), double = 0, double = 0);
        virtual void onMouseMotion(const SDL_MouseMotionEvent &event, bool = false, double = 0, double = 0, bool dontSend = false),
                     onKeyboard(const SDL_KeyboardEvent &event), animate(Uint32 timestep), setPosition(const Vector3D &position),
                     setPosition(double),  look(), vectorsFromAngles(bool = true, bool force = false, bool dontSend = false),
                     addTheta(double, bool clamp = false), addPhi(double, bool dontSend = false)/*, doCuffJob()*/, addRoll(double), setRoll(double), setPositionCommon()/*, setPosition(Position)*/, checkChunk(); // don't save roll (on server side because it is a temporary parameter ?) and for vehicles ?
        double m_theta, m_phi, m_roll; // degrees
    protected:
        double F5theta, F5phi;
        typedef std::map<SDL_Keycode, bool> KeyStates; // typedef ? - is just an alias
        KeyStates keystates;
        Vector3D leftTmp, head, up;
};

void changeF5Bool(), changeF7Bool(), setF5Bool(bool = false), setF7Bool(bool, bool = false), changeF5Distance(double F5Distance = DEFAULT_F5_DISTANCE), setAllInteractionEnabled(bool = false); // true could be a default case for setAllInteractionEnabled (like resetting earlier status or just use default argument as the default type value)
//#include "../../Collision/partitioning.h" // no such file or directory lol
bool getF7Bool()/*, isCollided(OBB, OBB)*/, getAllInteractinEnabled(); // for the moment is only foot movements
int getF5Bool(); // unsigned short ?

extern bool walking;
extern double F5_DISTANCE;
extern glm::vec3 inclinaison, origin, target;
//#include "../../../2D/vector2d.h"

//Vector3D getVec3(Vector2D vec2D);

#endif
