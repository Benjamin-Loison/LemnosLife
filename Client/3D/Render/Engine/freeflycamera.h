#ifndef FREEFLYCAMERA_H 
#define FREEFLYCAMERA_H
#define GLEW_STATIC
#include <glew.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include "vector3d.h" 
#include <map> 
#include <string> 
#include <SDL.h> 

extern bool walking; 

class FreeFlyCamera 
{ 
    public:
        Vector3D _position, _target, _cameraPosition, _F5CameraPosition, _F5CameraTarget; 
        FreeFlyCamera(const Vector3D &position = Vector3D(0, 0, 0)); 
        virtual void OnMouseMotion(const SDL_MouseMotionEvent &event), OnKeyboard(const SDL_KeyboardEvent &event), animate(Uint32 timestep), setPosition(const Vector3D &position), setPosition(double),  look();
    protected: 
        double _theta, _phi, _F5theta, _F5phi; 
        typedef std::map<SDL_Keycode, bool> KeyStates; 
        KeyStates _keystates;
        Vector3D _forward, _forwardTmp, _left, _leftTmp, _head, _up; 
        void VectorsFromAngles();
}; 

void changeF5Bool(), changeF7Bool(), setF7Bool(bool);
bool getF7Bool();
int getF5Bool();

#endif