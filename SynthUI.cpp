#include "SynthUI.h"

SynthUI::SynthUI(SynthCore * synthC, SynthSeq *sequencerObj, SynthCoreModMatrix * mMatrix) {
    tft.init();
    tft.setRotation(7);
    tft.fillScreen(TFT_BLACK);

    synthCore = synthC;
    seq = sequencerObj;
    matrix = mMatrix;

    isMainMenu = true;

    tftHeight = tft.getViewportWidth();
    tftWidth = tft.getViewportHeight();

    menuItemWidth = (tftWidth - (2 * SCREEN_MARGIN)) / MAX_ROWS;
    menuItemHeight = (tftHeight - (2 * SCREEN_MARGIN) - TOP_BAR_HEIGHT) / MAX_ROWS;

    mainSprite.setRotation(7);
    mainSprite.setColorDepth(8);
    mainSprite.createSprite(tftWidth, tftHeight);

    loadModules(synthCore->getModules(), synthCore->getNumModules());
}

void SynthUI::loadModules(SynthCoreObject * synthCoreModules, int numMods) {
    numMenuItems = numMods;

    //SynthCore modules
    for(int x = 0; x < numMenuItems; x++){
        modules[x] = new SynthUIObject(&synthCoreModules[x]);
    }

    //Custom modules
    modules[numMenuItems] = new SynthUIObject(new SynthUISequencer(tftHeight,tftWidth, TOP_BAR_HEIGHT, SCREEN_MARGIN, &theme, &mainSprite, seq), "Sequencer");
    numMenuItems++;
    modules[numMenuItems] = new SynthUIObject(new SynthUIModMatrix(tftHeight,tftWidth, TOP_BAR_HEIGHT, SCREEN_MARGIN, &theme, &mainSprite, matrix), "ModMatrix");
    numMenuItems++;
}

bool SynthUI::isMenu() {
    return isMainMenu;
}

void SynthUI::generateAndDisplay(){
    generateDisplay();

    mainSprite.pushSprite(0,0);
}

void SynthUI::generateDisplay() {
    mainSprite.fillSprite(theme.THEME_BACKGROUND);
    mainSprite.setTextColor(theme.THEME_TEXT);  // White text, no background colour
    mainSprite.setTextSize(2);           // Font x2 for title text

    drawTitleBar();

    mainSprite.setCursor(1,1);

    //Now choose what we display
    if(isMainMenu) {
        displayMainMenu();
    } else {
        mainSprite.print(modules[selectedMenuItem]->getName());
        if(!modules[selectedMenuItem]->isCustomScreen()) {
            displayParameterScreen2();
        } else {
            modules[selectedMenuItem]->generateScreen(selectedParameter);
        }
    }

}

void SynthUI::drawTitleBar() {
    int iconsFromTop = SCREEN_MARGIN + ((TOP_BAR_HEIGHT /2) - (TOP_BAR_ICON_SIZE/2));
    int playIconLeft = tftWidth/3 * 2;

    mainSprite.fillRect(0,0,tftWidth,TOP_BAR_HEIGHT - 1,theme.THEME_BACKGROUD_TOP_BAR);
    mainSprite.setTextColor(theme.THEME_TEXT_TOP_BAR);
    mainSprite.setTextSize(2); 

    //Is the synth playing?
    if(seq->isPlaying()) {
        mainSprite.fillTriangle(playIconLeft,iconsFromTop , 
                                    playIconLeft, iconsFromTop + TOP_BAR_ICON_SIZE, 
                                    playIconLeft + TOP_BAR_ICON_SIZE, iconsFromTop + (TOP_BAR_ICON_SIZE / 2), 
                                    theme.THEME_TEXT_TOP_BAR);
    }

    //Anything in the clipboard?
    mainSprite.drawRect(300,iconsFromTop, 
                                TOP_BAR_ICON_SIZE, TOP_BAR_ICON_SIZE,theme.THEME_TEXT_TOP_BAR);
    
    if(clipboardInUse) {
        mainSprite.fillRect(300 + TOP_BAR_ICON_MARGIN,iconsFromTop + TOP_BAR_ICON_MARGIN, 
                                TOP_BAR_ICON_SIZE - (2 * TOP_BAR_ICON_MARGIN), TOP_BAR_ICON_SIZE - (2 * TOP_BAR_ICON_MARGIN), 
                                theme.THEME_TEXT_TOP_BAR);
    }

    //Show volume
    mainSprite.fillTriangle(240, iconsFromTop + TOP_BAR_ICON_SIZE , 
                                240 + TOP_BAR_ICON_SIZE, iconsFromTop  + 3, 
                                240 + TOP_BAR_ICON_SIZE, iconsFromTop + TOP_BAR_ICON_SIZE, 
                                theme.THEME_TEXT_TOP_BAR);

    mainSprite.setCursor(255,1);
    mainSprite.print(synthCore->getVolume());

    mainSprite.setTextColor(theme.THEME_TEXT);
}

void SynthUI::displayMainMenu() {
    byte currentItem = 0;

    mainSprite.print("Menu");
    
    for(byte y = 0; y < MAX_ROWS; y++) {
        for(byte x = 0; x < MAX_COLUMNS; x++) {
            currentItem = x + (y * MAX_COLUMNS);

            if(currentItem < numMenuItems) { 
                mainSprite.setCursor(x * menuItemWidth + MENU_INNER_MARGIN,(y * menuItemHeight) + TOP_BAR_HEIGHT + MENU_INNER_MARGIN);
                mainSprite.setTextSize(1); // Font size scaling is x1

                //Draw rect
                if(currentItem == selectedMenuItem) {
                    mainSprite.fillRoundRect(SCREEN_MARGIN + (x * menuItemWidth),(y * menuItemHeight) + (SCREEN_MARGIN + TOP_BAR_HEIGHT), menuItemWidth, menuItemHeight,2, theme.THEME_BOX_HIGHLIGHT);
                    mainSprite.setTextColor(theme.THEME_TEXT_SELECTED);  // Invert the text colour
                } else {
                    mainSprite.drawRoundRect(SCREEN_MARGIN + (x * menuItemWidth),(y * menuItemHeight) + (SCREEN_MARGIN + TOP_BAR_HEIGHT), menuItemWidth, menuItemHeight,2, theme.THEME_BOX_OUTLINE);
                    mainSprite.setTextColor(theme.THEME_TEXT);  // White text, no background colour
                }

                //Draw text
                mainSprite.print(modules[currentItem]->getName());
            }
        }
    }
}

void SynthUI::displayParameterScreen2() {
    //SPECIAL HANDLERS
    if(modules[selectedMenuItem]->getModuleType() == SYNTH_MODULE_TYPE::ENVELOPE) {
        displaySpecialHandlerEnvelope();
    }

    //DISPLAY PARAMETERS
    byte currentItem = 0;

    for(byte y = 0; y < MAX_ROWS; y++) {
        for(byte x = 0; x < MAX_COLUMNS; x++) {
            currentItem = x + (y * MAX_COLUMNS);

            if(currentItem < modules[selectedMenuItem]->getNumParameters()) {
                mainSprite.setCursor(x * menuItemWidth + MENU_INNER_MARGIN,(y * menuItemHeight) + TOP_BAR_HEIGHT + MENU_INNER_MARGIN);
                mainSprite.setTextSize(1); // Font size scaling is x1
                
                //Draw rect
                if(currentItem == selectedParameter) {
                    mainSprite.fillRoundRect(SCREEN_MARGIN + (x * menuItemWidth),(y * menuItemHeight) + (SCREEN_MARGIN + TOP_BAR_HEIGHT), menuItemWidth, menuItemHeight,2, theme.THEME_BOX_HIGHLIGHT);
                    mainSprite.setTextColor(theme.THEME_TEXT_SELECTED);  // Invert the text colour
                } else {
                    mainSprite.drawRoundRect(SCREEN_MARGIN + (x * menuItemWidth),(y * menuItemHeight) + (SCREEN_MARGIN + TOP_BAR_HEIGHT), menuItemWidth, menuItemHeight,2, theme.THEME_BOX_OUTLINE);
                    mainSprite.setTextColor(theme.THEME_TEXT);  // White text, no background colour
                }
                //Draw parameter name                        
                mainSprite.print(modules[selectedMenuItem]->parameters[currentItem]->getName());

                //Value
                mainSprite.setCursor(x * menuItemWidth + MENU_INNER_MARGIN,(y * menuItemHeight) + TOP_BAR_HEIGHT + (menuItemHeight/2));
                mainSprite.setTextSize(2); 
                mainSprite.print(modules[selectedMenuItem]->parameters[currentItem]->getValueString());   
            } else {
                break;
            }
        }
    } 
}

//Displays the envelope graphically behind the scenes
void SynthUI::displaySpecialHandlerEnvelope() {
    if(modules[selectedMenuItem]->getModuleType() == SYNTH_MODULE_TYPE::ENVELOPE) {
        int attack = modules[selectedMenuItem]->parameters[0]->getValueInt();
        int decay = modules[selectedMenuItem]->parameters[1]->getValueInt();
        int sustain = modules[selectedMenuItem]->parameters[2]->getValueInt();
        int release = modules[selectedMenuItem]->parameters[3]->getValueInt();
        int attackLevel = map(modules[selectedMenuItem]->parameters[4]->getValueByte(),0,255,0,(tftHeight - TOP_BAR_HEIGHT));      
        int decayLevel = map(modules[selectedMenuItem]->parameters[5]->getValueByte(),0,255,0,(tftHeight - TOP_BAR_HEIGHT));
        
        
        int envelopeTotalTime = attack + decay + sustain + release;
        int bottomScreen = tftWidth;

        //Map values to actual screen
        attack = map(attack,0,envelopeTotalTime,0,tftHeight);
        decay = map(decay,0,envelopeTotalTime,0,tftHeight);
        sustain = map(sustain,0,envelopeTotalTime,0,tftHeight);
        release = map(release,0,envelopeTotalTime,0,tftHeight);


        mainSprite.drawLine(0, bottomScreen, attack, bottomScreen - attackLevel, theme.THEME_ENVELOPE_LINE);
        mainSprite.drawLine(attack, bottomScreen - attackLevel, attack + decay, bottomScreen - decayLevel, theme.THEME_ENVELOPE_LINE);
        mainSprite.drawLine(attack + decay, bottomScreen - decayLevel, attack + decay + sustain, bottomScreen - decayLevel, theme.THEME_ENVELOPE_LINE);
        mainSprite.drawLine(attack + decay + sustain, bottomScreen - decayLevel, attack + decay + sustain + release, bottomScreen, theme.THEME_ENVELOPE_LINE);
    }
}

void SynthUI::incrementSelectedParameter(bool shiftPressed) {
    if(isMenu()) {
        if (synthCore->getVolume() + VOLUME_ADJUST_STEP <= synthCore->getMaxVolume()) {
            synthCore->setVolume(synthCore->getVolume() + VOLUME_ADJUST_STEP);
        } else {
            synthCore->setVolume(synthCore->getMaxVolume());
        }
    } else {
        modules[selectedMenuItem]->increaseParameter(selectedParameter, shiftPressed);
    }
}

void SynthUI::decrementSelectedParameter(bool shiftPressed) {
    if(isMenu()) {
        if (synthCore->getVolume() - VOLUME_ADJUST_STEP >= 0) {
            synthCore->setVolume(synthCore->getVolume() - VOLUME_ADJUST_STEP);
        } else {
            synthCore->setVolume(0);
        }
    } else {
        modules[selectedMenuItem]->decreaseParameter(selectedParameter, shiftPressed);
    }
}

void SynthUI::handleMultiButton(bool shiftPressed) {
    if(isMenu()) {
        //Clear clipboard
        if(shiftPressed) {
            clipboardInUse = false;
        }
    } else { 
        if(!modules[selectedMenuItem]->isCustomScreen()) {   
            //If we're in a module screen copy or paste the module settings
            if(!shiftPressed) {          
                if(!clipboardInUse) {
                    //COPY
                    clipboard = synthCore->getModule(selectedMenuItem);
                    clipboardInUse = true;
                } else {
                    //PASTE
                    if(modules[selectedMenuItem]->getModuleType() == clipboard->getModuleType()) {
                        synthCore->copyModule(selectedMenuItem, clipboard);
                        clipboardInUse = false;
                    }
                }
            }
        } else {
            modules[selectedMenuItem]->pressMultiButton(selectedParameter, shiftPressed);
        }
    }
}

void SynthUI::incrementSelectedItem(bool shiftPressed){
    if(!shiftPressed) {
        if(isMainMenu){
            selectedMenuItem++;

            if(selectedMenuItem >= numMenuItems) {
                selectedMenuItem = 0;
            }
        } else {
            selectedParameter++;

            //HACK
            if(modules[selectedMenuItem]->getName() == "Sequencer") {
                if(selectedParameter >= seq->getSequenceSteps()) {
                    selectedParameter = 0;
                }
                return;
            }

            if(selectedParameter >= modules[selectedMenuItem]->getNumParameters()) {
                selectedParameter = 0;
            }
        }
    } else {
        if(!isMainMenu) {
            modules[selectedMenuItem]->increaseParameter(selectedParameter, shiftPressed);
        }
    }
}

void SynthUI::decrementSelectedItem(bool shiftPressed) {
    if(!shiftPressed) {
        if(isMainMenu) {
            selectedMenuItem--;

            if(selectedMenuItem < 0) {
                selectedMenuItem = numMenuItems - 1;
            }
        } else {
            selectedParameter--;

            //HACK
            if(modules[selectedMenuItem]->getName() == "Sequencer") {
                if(selectedParameter < 0) {
                    selectedParameter = seq->getSequenceSteps() - 1;
                }
                return;
            }

            if(selectedParameter < 0) {
                selectedParameter = modules[selectedMenuItem]->getNumParameters() - 1;
            }
        }
    } else {
        if(!isMainMenu) {
            modules[selectedMenuItem]->decreaseParameter(selectedParameter, shiftPressed);
        }
    }
}

void SynthUI::returnToMenu() {
    isMainMenu = true;
}

void SynthUI::openSelectedMenuItem() {
    isMainMenu = false;
    selectedParameter = 0;
}

bool SynthUI::getSeqUpdate() {
    if(modules[selectedMenuItem]->getName() == "Sequencer" && seq->isPlaying()) {
        return true;
    } else {
        return false;
    }
}
