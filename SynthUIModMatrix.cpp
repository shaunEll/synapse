#include "SynthUIModMatrix.h"

SynthUIModMatrix::SynthUIModMatrix(): SynthUICustomScreen(240, 320, 5, 3, NULL, NULL){
        currentState = MATRIX_INTERNAL_STATE::INVALID;
    }

SynthUIModMatrix::SynthUIModMatrix(int tHeight, int tWidth, byte topHeight, byte margins, SynthUITheme * newTheme, TFT_eSprite * sprt, SynthCoreModMatrix * mMatrix) :
          SynthUICustomScreen(tHeight, tWidth, topHeight, margins, newTheme, sprt) {
            matrix = mMatrix;
            currentState = MATRIX_INTERNAL_STATE::CONNECTIONS;
        }
    
void SynthUIModMatrix::generateScreen(byte selectedP) {
    byte fromTop = pageMargins + topBarHeight;
    byte fromLeft = pageMargins;
    byte fromRight = pageMargins;

    switch(currentState) {
        case MATRIX_INTERNAL_STATE::CONNECTIONS:
            seqSprite->setTextSize(2); 

            //CURRENTLY SELECTED STEP
            seqSprite->fillRect(fromLeft, fromTop + (selectedP * MATRIX_ROW_HEIGHT) , tftWidth - (fromLeft + fromRight), MATRIX_ROW_HEIGHT, theme->THEME_BOX_HIGHLIGHT);

            for(int x = 0; x < matrix->getNumConnections(); x++) {
                seqSprite->drawRect(fromLeft, fromTop + (x * MATRIX_ROW_HEIGHT), tftWidth - (fromLeft + fromRight), MATRIX_ROW_HEIGHT, theme->THEME_BOX_OUTLINE);

                if(x == selectedP) {
                      seqSprite->setTextColor(theme->THEME_TEXT_SELECTED);
                } else {
                      seqSprite->setTextColor(theme->THEME_TEXT);
                }

                seqSprite->setCursor(fromLeft + 2,fromTop + (x * MATRIX_ROW_HEIGHT) + 1);
                seqSprite->print(matrix->getConnectionString(selectedP));
            } 

            
            break;
          
          default:
            break;
    }

    seqSprite->setTextColor(theme->THEME_TEXT);
    seqSprite->setTextSize(1); // Font size scaling is x1
}

void SynthUIModMatrix::increaseMenu(byte selectedP) {
}

void SynthUIModMatrix::decreaseMenu(byte selectedP) {
}

void SynthUIModMatrix::increaseParameter(byte selectedP, bool shiftisPressed) {
    switch(currentState) {
        case MATRIX_INTERNAL_STATE::CONNECTIONS:
            matrix->editConnection(selectedP, matrix->getWetPercent(selectedP) + 1);
            break;
        
        default:
          break;
    }    
}

void SynthUIModMatrix::decreaseParameter(byte selectedP, bool shiftisPressed) {
    switch(currentState) {
        case MATRIX_INTERNAL_STATE::CONNECTIONS:
            matrix->editConnection(selectedP, matrix->getWetPercent(selectedP) - 1);
            break;
          
        default:
          break;
    } 
}

void SynthUIModMatrix::pressMultiButton(byte selectedP, bool shiftisPressed) {
}
