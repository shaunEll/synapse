#ifndef SynthParameter_h
#define SynthParameter_h

#include <MozziGuts.h>
#include <Line.h>
#include "SynthModifiableParameter.h"


#define PARAM_SHIFT_FACTOR 5
#define LINE_STEPS AUDIO_RATE / 4

#define SYNTH_P_OSC_START 0
#define SYNTH_P_OSC_LENGTH 8
#define SYNTH_P_FILTER_START 8
#define SYNTH_P_FILTER_LENGTH 3
#define SYNTH_P_LFO_START 11
#define SYNTH_P_LFO_LENGTH 5

enum SYNTH_P {
    OSC_SINE, //0
    OSC_SAW,
    OSC_TRIANGLE,
    OSC_SQUARE,
    OSC_WHITENOISE,
    OSC_CHUM78, //5
    OSC_SQ2,
    OSC_TR2,
    FILTER_LOWPASS, //8
    FILTER_HIGHPASS,
    FILTER_BANDPASS,
    LFO_SINE, //11
    LFO_SAW,
    LFO_TRIANGLE,
    LFO_SQUARE,
    LFO_WHITENOISE
};

enum SYNTH_P_TYPE {
    P_BYTE,
    P_BOOL,
    P_INT,
    P_ENUM,
    P_FLOAT,
    P_NONE
};

class UpdatableParameterObject {
    public:
        virtual void processParameterUpdate(byte parameterID) = 0;
};

class SynthParameter : public SynthModifiableParameter {
    protected:
        String paramName;
        String parentName;
        byte id;
        SYNTH_P_TYPE paramType;

        //CURRENT/ACTUAL VALUE
        int * parameterInt;
        float * parameterFloat;
        byte * parameterByte;
        bool * parameterBool;
        SYNTH_P * parameterEnum;

        //VALUE CONFIGURED IN THE UI
        int configuredValueInt;
        float configuredValueFloat;
        byte configuredValueByte;
        bool configuredValueBool;
        SYNTH_P configuredValueEnum;

        //LINE FOR NUMERIC VALUES
        Line<int> intLine;
        Line<float> floatLine;
        Line<byte> byteLine;

        byte enumStartPosition, enumAmount, enumIndex;
        float changeFactor, shiftFactor, min_value, max_value, onePercent, modValue;

        bool modified = false;
        bool modifier = false;

        UpdatableParameterObject * callbackFunction;

        void setValueInt(int nValue, bool setCurrentValue = false);
        void setValueByte(byte nValue, bool setCurrentValue = false);
        void setValueFloat(float nValue, bool setCurrentValue = false);
        void setValueBool(bool nValue, bool setCurrentValue = false);
        void setValueEnum(int nValue, bool setCurrentValue = false);

    public:       
        SynthParameter(String newName, byte newId, String parentObj, float chgFac, float minV, float maxV, UpdatableParameterObject * callback_ptr, bool isMod = false); 
        SynthParameter(String newName, byte newId, String parentObj, int * param, float chgFac, float minV, float maxV, UpdatableParameterObject * callback_ptr, bool isMod = false); 
        SynthParameter(String newName, byte newId, String parentObj, float * param, float chgFac, float minV, float maxV, UpdatableParameterObject * callback_ptr, bool isMod = false); 
        SynthParameter(String newName, byte newId, String parentObj, byte * param, float chgFac, float minV, float maxV, UpdatableParameterObject * callback_ptr, bool isMod = false); 
        SynthParameter(String newName, byte newId, String parentObj, bool * param, UpdatableParameterObject * callback_ptr, bool isMod = false); 
        SynthParameter(String newName, byte newId, String parentObj, SYNTH_P * param, byte eStart, byte eLength, UpdatableParameterObject * callback_ptr, bool isMod = false); 

        String getName() { return paramName; }
        String getNameShort() { return paramName.substring(0,4); }
        String getParentName() { return parentName; }
        byte getId() { return id; }
        bool isModifier() { return modifier; }
        bool isModified() { return modified; }

        //UI Functions
        void increaseParameter(bool shift, bool affectCurrent = false);
        void decreaseParameter(bool shift, bool affectCurrent = false);
        String getValueString(bool showCurrentValue = false);
        int getValueInt(bool showCurrentValue = false);
        byte getValueByte(bool showCurrentValue = false);
        
        void applyModifier(SynthMatrixConnection * modifier, bool setCurrentValue = true) override;
        void resetState() override;
        void process() override;
};

#endif