#ifndef SynthCoreObject_h
#define SynthCoreObject_h

#include "Arduino.h"
#include "SynthParameter.h"

#define NUM_OSCILLATORS 3
#define NUM_ENVELOPES 2
#define NUM_FILTERS 2
#define NUM_LFOS 2
#define MAX_PARAMETERS 12

enum SYNTH_MODULE_TYPE {
    OSCILLATOR,
    FILTER,
    ENVELOPE,
    LFO,
    MODMATRIX,
    CUSTOM
};

class SynthCoreObject {
    protected:
        String name;
        int indexId;
        bool modifier = false;
        SYNTH_MODULE_TYPE type; 

        byte numParameters = 0;

    public:       
        SynthCoreObject(String nName, int nId, SYNTH_MODULE_TYPE nType, bool isMod = false);
        SynthCoreObject(String nName, int nId, SYNTH_MODULE_TYPE nType, byte nParams, bool isMod);

        String getName();
        int getIndex();
        SYNTH_MODULE_TYPE getModuleType();
        bool isModifier();

        SynthParameter * parameters[MAX_PARAMETERS];
        int getNumParameters();

        virtual void init() = 0;
        virtual void copyObject(SynthCoreObject * obj) = 0;
};

#endif