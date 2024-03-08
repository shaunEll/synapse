#ifndef SynthModifiableParameter_h
#define SynthModifiableParameter_h

#include "SynthMatrixConnection.h"

class SynthModifiableParameter {
    public:
        virtual void applyModifier(SynthMatrixConnection * modifier, bool setCurrentValue = true) = 0;
        virtual void resetState() = 0;
        virtual void process() = 0;
};

#endif