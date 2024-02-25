#ifndef SynthParameter_h
#define SynthParameter_h

#include <MozziGuts.h>
#include <Line.h>

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

class SynthMatrixConnection;

class SynthParameter{
    protected:
        char * paramName;
        char * parentName;
        byte id;

        void (*callbackFunction)(); 

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

    private:
        void setValueInt(int nValue, bool setCurrentValue = false);
        void setValueByte(byte nValue, bool setCurrentValue = false);
        void setValueFloat(float nValue, bool setCurrentValue = false);
        void setValueBool(bool nValue, bool setCurrentValue = false);
        void setValueEnum(int nValue, bool setCurrentValue = false);

    public:
        SynthParameter(char * newName, byte newId, char * parentObj, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); 
        SynthParameter(char * newName, byte newId, char * parentObj, int * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); 
        SynthParameter(char * newName, byte newId, char * parentObj, float * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); 
        SynthParameter(char * newName, byte newId, char * parentObj, byte * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); 
        SynthParameter(char * newName, byte newId, char * parentObj, bool * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); 
        SynthParameter(char * newName, byte newId, char * parentObj, SYNTH_P * param, byte eStart, byte eLength, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false); // :

        char * getName() { return paramName; }
        char * getNameShort() { return strncpy("%.*s", 0, *paramName + 4); }
        char * getParentName() { return parentName; }
        byte getId() { return id; }
        bool isModifier() { return modifier; }
        bool isModified() { return modified; }

        //UI Functions
        void increaseParameter(bool shift, bool affectCurrent = false);
        void decreaseParameter(bool shift, bool affectCurrent = false);
        String getValueString(bool showCurrentValue = false);
        int getValueInt(bool showCurrentValue = false);
        byte getValueByte(bool showCurrentValue = false);

        //Modifers
        void applyModifier(SynthMatrixConnection * modifier, bool setCurrentValue = true);
        void resetState();
        void process();
};

#endif