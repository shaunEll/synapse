#ifndef SynthCoreObject_h
#define SynthCoreObject_h

#include "SynthParameter.h"

#define MAX_PARAMETERS 12

#define NUM_OSCILLATORS 3
#define NUM_ENVELOPES 2
#define NUM_FILTERS 2
#define NUM_LFOS 2

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
        byte numParameters = 0;
        char * name;
        int indexId;
        bool modifier = false;

        SYNTH_MODULE_TYPE type; 

    public:       
        SynthCoreObject(char * nName, int nId, SYNTH_MODULE_TYPE nType, bool isMod = false) {
            name = nName;
            indexId = nId;
            type = nType;
            modifier = isMod;
        }

        SynthParameter * parameters[MAX_PARAMETERS];
        char * getName() { return name; }
        int getIndex() { return indexId; }
        SYNTH_MODULE_TYPE getModuleType() { return type; }
        int getNumParameters() { return numParameters; }
        bool isModifier() { return modifier; }
        byte getParameterByName(char * pName) {
            for(int x = 0; x < numParameters; x++) {
                if(* parameters[x]->getName() == * pName) {
                    return x;
                }
            }

            return 255;
        }

        virtual void init() = 0;
        virtual void copyObject(SynthCoreObject * obj) = 0;

        virtual byte * getModifierValueByte() = 0;
        virtual int * getModifierValueInt() = 0;
        virtual float * getModifierValueFloat() = 0;
        virtual bool * getModifierValueBool() = 0;
        virtual SYNTH_P * getModifierValueEnum() = 0;
};

#endif