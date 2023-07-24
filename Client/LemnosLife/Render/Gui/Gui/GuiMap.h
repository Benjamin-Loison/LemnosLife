#ifndef DEF_GUIMAP
#define DEF_GUIMAP

#include "Gui.h"
#include <vector>
#include <string>
#include "../../../../2D/vector2d.h"
#include "TickBox.h"

// at 16000,16000 with chunkView 150 with zoom 1.3, we have perfectly everything

class GuiMap : public Gui
{
public:
    void initGui(), resizeGui(), renderGui(), quickInit();
    std::vector<Textfield> m_textfields;
private:
    std::vector<TickBox> m_tickBoxs; // can't do without a vector ?! or have to do an empty constructor for TickBox ?
};

extern double zoom, DEBUG_SIZE, mappingOffsetX, mappingOffsetY;

void resetMap2D(), initMapping(), initMapSize(), resetMarker();
extern unsigned int lowerBound, upperBound;
double toX(double x), toY(double y), getIgX(double x), getIgY(double y), getX(double), getY(double);
extern std::vector<Vector2D> itinerary;
extern bool mapping, displayMapAfterGameLoad, seePlayers, isMap2DLoaded;
extern unsigned short mappingPrecision, mappingRange;
extern std::map<std::pair<unsigned short, unsigned short>, GLuint> mappingTiles;
std::pair<unsigned short, unsigned short> getTile(double x, double y);
extern std::vector<std::string> modifiedAltitudes;

#endif
