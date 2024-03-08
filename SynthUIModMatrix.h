#ifndef SynthUIModMatrix_h
#define SynthUIModMatrix_h

#include "SynthUICustomScreen.h"
#include "SynthModMatrix.h"
#include "SynthUITheme.h"

#define MATRIX_ROW_HEIGHT 25

enum MATRIX_INTERNAL_STATE {
    CONNECTIONS,
    EDITCONNECTION,
    NEWCONNECTION,
    INVALID
};

class SynthUIModMatrix: public SynthUICustomScreen {
    protected:
      SynthCoreModMatrix * matrix;
      MATRIX_INTERNAL_STATE currentState;

      SynthUIPopup popup;
      
    public:
      SynthUIModMatrix();

      SynthUIModMatrix(int tHeight, int tWidth, byte topHeight, byte margins, SynthUITheme * newTheme, TFT_eSprite * sprt, SynthCoreModMatrix * mMatrix);
      
      void generateScreen(byte selectedP) override;
      void increaseMenu(byte selectedP) override;
      void decreaseMenu(byte selectedP) override;
      void increaseParameter(byte selectedP, bool shiftisPressed = false) override;
      void decreaseParameter(byte selectedP, bool shiftisPressed = false) override;
      void pressMultiButton(byte selectedP, bool shiftisPressed = false) override;
};

#endif