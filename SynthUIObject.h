#ifndef SynthModifierObject_h
#define SynthModifierObject_h

#include "Arduino.h"
#include "SynthCoreObject.h"
#include "SynthUICustomScreen.h"

class SynthUIObject {
    SynthUICustomScreen * screen;
    SynthCoreObject * module;   
    byte numParameters;

    bool custom;
    String name;

    public:
        SynthParameter * parameters[12];

        SynthUIObject(SynthUICustomScreen * newScreen, String newName);
        SynthUIObject(SynthCoreObject * newObject);

        bool isCustomScreen();

        SYNTH_MODULE_TYPE getModuleType();

        String getName();

        byte getNumParameters();

        void generateScreen(byte selectedParameter);

        void increaseParameter(byte selectedParameter, bool shiftPressed = false);

        void decreaseParameter(byte selectedParameter, bool shiftPressed = false);

        void pressMultiButton(byte selectedParameter, bool shiftPressed = false);
};

#endif