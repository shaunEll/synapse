#ifndef SynthMatrixConnection_h
#define SynthMatrixConnection_h

#include "Arduino.h"

#define DEFAULT_WET_PERCENT 50

class SynthModifierObject;
class SynthParameter;

class SynthMatrixConnection {
    SynthModifierObject * modSource;
    SynthParameter * targetParam;
    byte percentValue;

    public:
        SynthMatrixConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue);
        SynthMatrixConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam);

        int getModValueInt();
        byte getModValueByte();
        float getModValueFloat();
        bool getModValueBool();

        void processConnectionUpdate();
        void processConnectionControl();
        void restoreOriginalValue();
        void updateWetPercent(byte newWet);
        byte getWetPercent();
        String toString();
};

#endif