#ifndef DEF_GUISTRUCTURES
#define DEF_GUISTRUCTURES

#include "Gui.h"
#include <vector>
#include <string>

class GuiStructures : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui(), onTextfieldInput();
        std::vector<Textfield> m_textfields;
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false, button4Clicked = false, button5Clicked = false, button6Clicked = false, button7Clicked = false, button8Clicked = false, button9Clicked = false,
             button10Clicked = false, button11Clicked = false, button12Clicked = false, button13Clicked = false, button14Clicked = false, button15Clicked = false, button16Clicked = false, button17Clicked = false, button18Clicked = false, button19Clicked = false,
             button20Clicked = false, button21Clicked = false, button22Clicked = false, button23Clicked = false, button24Clicked = false;
    private:
        std::vector<Button> m_buttones;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked(), onButton4Clicked(), onButton5Clicked(), onButton6Clicked(), onButton7Clicked(), onButton8Clicked(), onButton9Clicked(), onButton10Clicked(), onButton11Clicked(),
             onButton12Clicked(), onButton13Clicked(), onButton14Clicked(), onButton15Clicked(), onButton16Clicked(), onButton17Clicked(), onButton18Clicked(), onButton19Clicked(), onButton20Clicked(), onButton21Clicked(), onButton22Clicked(), onButton23Clicked(),
             onButton24Clicked(), refreshStructure(bool force = false), reangleStructure(), reangleSelectedPart(), inverseSign(short = 1, short = 1, short = 1);
};

extern int selectedPartGuiStructures;
void refreshStructurePath(), computePointsCoordinates();
extern std::string tmpSelectedPartGuiStructures, structurePath;
extern std::vector<std::string> tmpSelectedPartGuiStructuresPointsCoordinates, tmpSelectedPartGuiStructuresPointsTextureCoordinates;
extern bool renderOutlineSelection;
extern unsigned short tmpSelectedPartGuiStructuresAngle;

std::string getLineByID(std::vector<std::string>, std::string), getStructureTexture(unsigned short partId);

#endif
