#ifndef DEF_GUIGAME
#define DEF_GUIGAME

#include "Gui.h"
#include <vector>
#include "../../../../3D/Render/Engine/API3D.h"
#include "../../../Map/User/View.h"
#include "../../../../Vehicles/Vehicle.h"

#define DEBUG_GL_ERR

//extern std::vector<std::vector<double>> debugLinesToInit;
extern std::vector</*std::pair<double, double>*/std::vector<double>> lineDebugToAdd;
extern std::vector<Line3D> lineDebug, markerLines;
extern bool isInGame, crosshairEnabled, testGraphicThread, testGraphicThreadForce, isFirstSpawn, needResetMap2D, markerZCorrect/*, sirenSwitch*/, removeVehiclesWanted, groundClearWanted,
       needVehicleGraphicUpdate, collisionRaytracing, needClearBulletImpacts, armRightChange, isProfiling/*, sitKeyPressed*/, clearGroundWanted;//, needHandRender;
extern int reloadStructureId;
void clearLineDebug(), reloadStruc(unsigned short id, bool force = false), addAnItems3DToRemove(unsigned int itemId, View);
extern unsigned short wantToZoom;
extern std::map<unsigned int, std::vector<View>> items3DToRemove;
extern std::vector<Vehicle*> vehiclesToRemove;
extern std::string drawFile, armRightUsername;
extern double markerX, markerY, markerZ, degreesArmRight0, degreesArmRight1;
extern std::vector<std::pair<std::string, std::string>> setPositionStates;
extern std::vector<std::pair<Vector3D, double>/*std::vector<Vector3D>*/> bulletImpactsToAdd;
extern std::vector<std::tuple<unsigned int, glm::vec3, glm::vec3>> structuresToAdd;
extern std::vector<std::tuple<unsigned int, glm::vec3, unsigned short>> structuresToRemove;
extern std::pair<unsigned int, unsigned short> itemsToSetInHand;

class GuiGame : public Gui
{
public:
    void initGui(), renderGui(), resizeGui();
    bool isDynamic();
private:
    unsigned short crosshairBottomLeftX, crosshairBottomLeftY, crosshairTopRightX, crosshairTopRightY;
};

#endif
