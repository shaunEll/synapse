
#ifndef SynthUICustomScreen_h
#define SynthUICustomScreen_h

#include "SynthUITheme.h"
#include "TFT_eSPI.h"

#define POPUP_MAX_TIME 2000
#define POPUP_MARGIN 2

class SynthUIPopup {
    public:
        SynthUIPopup() {
            popupTitle = "Not Configured";
            popupValue = 0;
            startTime = 0;
            isDisplaying = false;
        }

        SynthUIPopup(TFT_eSprite * sprt, SynthUITheme * newTheme, String title, int value, int x, int y, int width, int height) {
            popupSprite = sprt;
            popupTitle = title;
            popupValue = value;
            popupTheme = newTheme;

            popupX = x;
            popupY = y;
            popupWidth = width;
            popupHeight = height;

            startTime = 0;
            isDisplaying = false;
        }

        void display() {
            if(visible()) {
                    //frame
                    popupSprite->fillRect(popupX,popupY, popupWidth, popupHeight,popupTheme->THEME_BACKGROUND);
                    popupSprite->drawRect(popupX + POPUP_MARGIN,popupY + POPUP_MARGIN, popupWidth - POPUP_MARGIN * 2, popupHeight - POPUP_MARGIN * 2,popupTheme->THEME_BOX_OUTLINE);
                   
                    //title
                    popupSprite->setCursor(popupX + POPUP_MARGIN + 1,popupY + POPUP_MARGIN + 1);
                    popupSprite->setTextSize(1); // Font size scaling is x1
                    popupSprite->print(popupTitle);

                    //value
                    popupSprite->setTextSize(3); 
                    popupSprite->setTextDatum(MC_DATUM);
                    popupSprite->drawString(String(popupValue), popupX + popupWidth / 2, popupY + popupHeight / 2 + 2);

                    popupSprite->setTextSize(1); // Font size scaling is x1
            } 
        }

        bool visible() {
            if(millis() - startTime < POPUP_MAX_TIME) {
                isDisplaying = true;
            } else {
                isDisplaying = false;
            }

            return isDisplaying;
        }

        void show() {
            startTime = millis();
            display();
        }

        void show(int newValue) {
            popupValue = newValue;
            show();
        }

        void show(String newTitle, int newValue) {
            popupTitle = newTitle;
            show(newValue);
        }

        void hide() {
            startTime = 0;
            display();
        }

    protected:
        TFT_eSprite * popupSprite;
        SynthUITheme * popupTheme;

        String popupTitle;
        int popupValue;
        int popupX, popupY, popupWidth, popupHeight;

        long startTime = 0;
        bool isDisplaying = false;   
};

class SynthUICustomScreen {
    protected:
      byte numParameters = 0;
      int tftHeight, tftWidth;
      byte topBarHeight, pageMargins;

      SynthUITheme * theme;

    public:
        SynthUICustomScreen(int tHeight, int tWidth, byte topHeight, byte margins, SynthUITheme * newTheme, TFT_eSprite * sprt)
        {
            tftHeight = tHeight;
            tftWidth = tWidth;
            theme = newTheme;
            topBarHeight = topHeight;
            pageMargins = margins;

            seqSprite = sprt;
        }

        void setNumParameters(byte newNum) {
            numParameters = newNum;
        }

        byte getNumParameters() {
            return numParameters;
        }

        virtual void generateScreen(byte selectedParameter) = 0;
        virtual void increaseParameter(byte selectedP, bool shiftisPressed = false) = 0;
        virtual void decreaseParameter(byte selectedP, bool shiftisPressed = false) = 0;
        virtual void pressMultiButton(byte selectedP, bool shiftisPressed = false) = 0;
        virtual void increaseMenu(byte selectedP) = 0;
        virtual void decreaseMenu(byte selectedP) = 0;

        TFT_eSprite * seqSprite;        
};

#endif