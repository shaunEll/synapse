#ifndef SynthUI_h
#define SynthUI_h

#include "Arduino.h" 
#include "SPI.h"
#include "TFT_eSPI.h"
#include "SynthCore.h"
#include "SynthModMatrix.h"
#include "SynthSeq.h"
#include "SynthUITheme.h"
#include "SynthUIObject.h"
//#include "SynthUICustomScreen.h"
#include "SynthUISequencer.h"
#include "SynthUIModMatrix.h"

#define DEBUG_UI false

#define MAX_COLUMNS 4
#define MAX_ROWS 4
#define MAX_MENU_ITEMS MAX_COLUMNS * MAX_ROWS

#define SCREEN_MARGIN 5

#define MENU_INNER_MARGIN 5
#define TOP_BAR_HEIGHT 20
#define TOP_BAR_ICON_SIZE 10
#define TOP_BAR_ICON_MARGIN 2

#define VOLUME_ADJUST_STEP 1

class SynthUI {
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSprite mainSprite = TFT_eSprite(&tft);

    SynthCore * synthCore;
    SynthSeq * seq;
    SynthCoreModMatrix * matrix;
    SynthUIObject * modules[MAX_MENU_ITEMS];
    
    SynthUITheme theme = SynthUIDarkGreenTheme();
    SynthUISequencer * sequencerHandlerScreen;
    SynthUIModMatrix * modMatrixHandlerScreen;

    int tftHeight, tftWidth, menuItemWidth, menuItemHeight;

    //Menu state
    bool isMainMenu;
    int selectedMenuItem = 0;
    int selectedParameter = 0;
    int numMenuItems = 0;  

    //Clipboard
    bool clipboardInUse = false;
    SynthCoreObject * clipboard = nullptr; 

    public:
        SynthUI(SynthCore * synthC, SynthSeq *sequencerObj, SynthCoreModMatrix * mMatrix);
        
        void loadModules(SynthCoreObject * synthCoreModules, int numMods);

        bool isMenu();

        void generateAndDisplay();
        void generateDisplay();
        void drawTitleBar();
        void displayMainMenu();
        void displayParameterScreen2();
        void displaySpecialHandlerEnvelope();

        void incrementSelectedParameter(bool shiftPressed);
        void decrementSelectedParameter(bool shiftPressed);
        void handleMultiButton(bool shiftPressed);
        void incrementSelectedItem(bool shiftPressed = false);
        void decrementSelectedItem(bool shiftPressed = false);
        void returnToMenu();
        void openSelectedMenuItem();

        bool getSeqUpdate();
           
};

#endif