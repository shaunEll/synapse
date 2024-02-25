#include "SynthParameter.h"
#include "../matrix/SynthMatrixConnection.h"

//Base
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) {
    paramName = newName;
    id = newId;
    paramType = SYNTH_P_TYPE::P_NONE;

    parentName = parentObj;
    callbackFunction = callback_ptr;


    modifier = isMod;
    modified = false;

    changeFactor = chgFac;
    min_value = minV;
    max_value = maxV;

    shiftFactor = PARAM_SHIFT_FACTOR;
}

//Int constructor
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, int * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) :
    SynthParameter(newName, newId, parentObj, chgFac, minV, maxV, callback_ptr, isMod) {
    paramType = SYNTH_P_TYPE::P_INT;
    parameterInt = param;
    configuredValueInt = * param;
}

//Float constructor
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, float * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) :
    SynthParameter(newName, newId, parentObj, chgFac, minV, maxV, callback_ptr, isMod) {
    paramType = SYNTH_P_TYPE::P_FLOAT;
    parameterFloat = param;
    configuredValueFloat = * param;
}

//Byte constructor
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, byte * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) :
    SynthParameter(newName, newId, parentObj, chgFac, minV, maxV, callback_ptr, isMod) {
    paramType = SYNTH_P_TYPE::P_BYTE;
    parameterByte = param;
    configuredValueByte = * param;
}

//Bool constructor
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, bool * param, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) :
    SynthParameter(newName, newId, parentObj, chgFac, minV, maxV, callback_ptr, isMod) {
    paramType = SYNTH_P_TYPE::P_BOOL;
    parameterBool = param;
    configuredValueBool = * param;
}

//Enum constructor
SynthParameter::SynthParameter(char * newName, byte newId, char * parentObj, SYNTH_P * param, byte eStart, byte eLength, float chgFac, float minV, float maxV, void (*callback_ptr)(), bool isMod = false) :
    SynthParameter(newName, newId, parentObj, chgFac, minV, maxV, callback_ptr, isMod) {
    paramType = SYNTH_P_TYPE::P_ENUM;
    parameterEnum = param;
    configuredValueEnum = * param;

    enumStartPosition = eStart;
    enumAmount = eLength;
    enumIndex = eStart;
}

//UI Functions
void SynthParameter::increaseParameter(bool shift, bool affectCurrent = false) {
    switch(paramType) {
        case SYNTH_P_TYPE::P_INT:
            int iValue = (affectCurrent ? * parameterInt : configuredValueInt) + changeFactor * (shift ? shiftFactor : 1);
    
            if (iValue <= max_value) {
                setValueInt(iValue, affectCurrent);
            } else {
                setValueInt(max_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_BYTE:
            byte bValue = (affectCurrent ? * parameterByte : configuredValueByte) + changeFactor * (shift ? shiftFactor : 1);
    
            if (bValue <= max_value) {
                setValueByte(bValue, affectCurrent);
            } else {
                setValueByte(max_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_FLOAT:
            float fValue = (affectCurrent ? * parameterFloat : configuredValueFloat) + changeFactor * (shift ? shiftFactor : 1);
    
            if (fValue <= max_value) {
                setValueFloat(fValue, affectCurrent);
            } else {
                setValueFloat(max_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_BOOL:
            if(affectCurrent) {
                setValueBool(!(* parameterBool), affectCurrent);
            } else {
                setValueBool(!configuredValueBool, affectCurrent);
            }
            break;
        
        case SYNTH_P_TYPE::P_ENUM:
            if (enumIndex + 1 < (enumStartPosition + enumAmount)) {
                enumIndex++;
                setValueEnum(enumIndex, affectCurrent);
            } else {
                enumIndex = enumStartPosition;
                setValueEnum(enumIndex, affectCurrent);
            }
            break;

        default:
            return;
    }

    (* callbackFunction)();
}

void SynthParameter::decreaseParameter(bool shift, bool affectCurrent = false) {
    switch(paramType) {
        case SYNTH_P_TYPE::P_INT:
            int iValue = (affectCurrent ? * parameterInt : configuredValueInt) - changeFactor * (shift ? shiftFactor : 1);
    
            if (iValue >= min_value) {
                setValueInt(iValue, affectCurrent);
            } else {
                setValueInt(min_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_BYTE:
            byte bValue = (affectCurrent ? * parameterByte : configuredValueByte) - changeFactor * (shift ? shiftFactor : 1);
    
            if (bValue >= min_value) {
                setValueByte(bValue, affectCurrent);
            } else {
                setValueByte(min_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_FLOAT:
            float fValue = (affectCurrent ? * parameterFloat : configuredValueFloat) - changeFactor * (shift ? shiftFactor : 1);
    
            if (fValue >= min_value) {
                setValueFloat(fValue, affectCurrent);
            } else {
                setValueFloat(min_value, affectCurrent);
            }
            break;

        case SYNTH_P_TYPE::P_BOOL:
            if(affectCurrent) {
                setValueBool(!(* parameterBool), affectCurrent);
            } else {
                setValueBool(!configuredValueBool, affectCurrent);
            }
            break;
        
        case SYNTH_P_TYPE::P_ENUM:
            if (enumIndex - 1 >= enumStartPosition) {
                enumIndex--;
                setValueEnum(enumIndex, affectCurrent);
            } else {
                enumIndex = enumStartPosition + enumAmount - 1;
                setValueEnum(enumIndex, affectCurrent);
            }
            break;
        
        default:
            return;
    }

    (* callbackFunction)();
}

String SynthParameter::getValueString(bool showCurrentValue = false) {
    if(paramType == SYNTH_P_TYPE::P_ENUM) {
        switch (showCurrentValue ? * parameterEnum : configuredValueEnum) {
            case SYNTH_P::OSC_SINE:
                return "SIN";
                break;
            case SYNTH_P::OSC_SAW:
                return "SAW";
                break;
            case SYNTH_P::OSC_TRIANGLE:
                return "TRI";
                break;
            case SYNTH_P::OSC_SQUARE:
                return "SQU";
                break;
            case SYNTH_P::OSC_WHITENOISE:
                return "NOI";
                break;
            case SYNTH_P::OSC_CHUM78:
                return "C78";
                break;
            case SYNTH_P::OSC_SQ2:
                return "SQ2";
                break;
            case SYNTH_P::OSC_TR2:
                return "TR2";
                break;
            case SYNTH_P::FILTER_BANDPASS:
                return "BPF";
                break;
            case SYNTH_P::FILTER_HIGHPASS:
                return "HPF";
                break;
            case SYNTH_P::FILTER_LOWPASS:
                return "LPF";
                break;
            case SYNTH_P::LFO_SINE:
                return "SIN";
                break;
            case SYNTH_P::LFO_SAW:
                return "SAW";
                break;
            case SYNTH_P::LFO_TRIANGLE:
                return "TRI";
                break;
            case SYNTH_P::LFO_SQUARE:
                return "SQU";
                break;
            case SYNTH_P::LFO_WHITENOISE:
                return "NOI";
                break;
            default:
                return "N/A";
                break;
        }
    } else if (paramType == SYNTH_P_TYPE::P_BOOL) {
        if (showCurrentValue) {
            return (* parameterBool) ? "Yes" : "No";
        } else {
            return (configuredValueBool) ? "Yes" : "No";
        }
    } else if (paramType == SYNTH_P_TYPE::P_BYTE) {
        return String(showCurrentValue ? * parameterByte : configuredValueByte);
    } else if (paramType == SYNTH_P_TYPE::P_INT) {
        return String(showCurrentValue ? * parameterInt : configuredValueInt);
    } else if (paramType == SYNTH_P_TYPE::P_FLOAT) {
        return String(showCurrentValue ? * parameterFloat : configuredValueFloat);
    } else {
        return "N/A";
    }
}

int SynthParameter::getValueInt(bool showCurrentValue = false) {
    switch(paramType) {
        case SYNTH_P_TYPE::P_INT:
            return showCurrentValue ? * parameterInt : configuredValueInt;
            break;
        
        case SYNTH_P_TYPE::P_FLOAT:
            return (int)(showCurrentValue ? * parameterFloat : configuredValueFloat);
            break;
        
        case SYNTH_P_TYPE::P_BYTE:
            return (int)(showCurrentValue ? * parameterByte : configuredValueByte);
            break;
        
        case SYNTH_P_TYPE::P_BOOL:
            return (int)(showCurrentValue ? * parameterBool : configuredValueBool);
            break;

        default:
            return 0;
    }
}

byte SynthParameter::getValueByte(bool showCurrentValue = false) {
    switch(paramType) {
        case SYNTH_P_TYPE::P_INT:
            return (byte)(showCurrentValue ? * parameterInt : configuredValueInt);
            break;
        
        case SYNTH_P_TYPE::P_FLOAT:
            return (byte)(showCurrentValue ? * parameterFloat : configuredValueFloat);
            break;
        
        case SYNTH_P_TYPE::P_BYTE:
            return showCurrentValue ? * parameterByte : configuredValueByte;
            break;
        
        case SYNTH_P_TYPE::P_BOOL:
            return (byte)(showCurrentValue ? * parameterBool : configuredValueBool);
            break;

        default:
            return 0;
    }
}

//Matrix Functions <<__ applyModifier IS WIP
void SynthParameter::applyModifier(SynthMatrixConnection * modifier, bool setCurrentValue = true) {
    switch(paramType) {
        case SYNTH_P_TYPE::P_ENUM:
            enumIndex = map(modifier->getModValueByte(), 0, 255, enumStartPosition, (enumStartPosition + enumAmount - 1));
            setValueEnum(enumIndex, setCurrentValue);
            break;

        case SYNTH_P_TYPE::P_INT:
            onePercent = configuredValueInt / 100.0;
            modValue = (configuredValueInt * modifier->getModValueInt()) / configuredValueInt;
            int retValue = (int)(onePercent * (100 - modifier->getWetPercent())) + ((int)(modValue * modifier->getWetPercent()) >> 2);

            intLine.set(* parameterInt, retValue, LINE_STEPS);
            modified = true;
            break;
        
        case SYNTH_P_TYPE::P_FLOAT:
            onePercent = configuredValueFloat / 100.0;
            modValue = (configuredValueFloat * modifier->getModValueInt()) / configuredValueFloat;
            float fValue = (float)(onePercent * (100 - modifier->getWetPercent())) + ((int)(modValue * modifier->getWetPercent()) >> 2);

            floatLine.set(* parameterFloat, fValue, LINE_STEPS);
            modified = true;
            break;
        
        default:
            break;
    }
}

void SynthParameter::resetState() {
    switch (paramType) {
        case SYNTH_P_TYPE::P_INT:
            * parameterInt = configuredValueInt;
            modified = false;
            break;
        
        case SYNTH_P_TYPE::P_FLOAT:
            * parameterFloat = configuredValueFloat;
            modified = false;
            break;
        
        case SYNTH_P_TYPE::P_BOOL:
            * parameterBool = configuredValueBool;
            modified = false;
            break;

        case SYNTH_P_TYPE::P_BYTE:
            * parameterByte = configuredValueByte;
            modified = false;
            break;

        case SYNTH_P_TYPE::P_ENUM:
            * parameterEnum = configuredValueEnum;
            modified = false;
            break;
    
        default:
            break;
    }
}

void SynthParameter::process() {
    if(modified) {
        switch(paramType) {
            case SYNTH_P_TYPE::P_INT:
                setValueInt(intLine.next(), true);
                break;
            case SYNTH_P_TYPE::P_FLOAT:
                setValueFloat(floatLine.next(), true);
                break;
            case SYNTH_P_TYPE::P_BYTE:
                setValueByte(byteLine.next(), true);
                break;
        } 
    }
}

//Private methods
void SynthParameter::setValueInt(int nValue, bool setCurrentValue = false) {
    if(nValue >= min_value && nValue <= max_value) {
        if(!setCurrentValue) {
            configuredValueInt = nValue;
        } else if (setCurrentValue) {
            * parameterInt = nValue;
            modified = true;
        }
    }
}

void SynthParameter::setValueByte(byte nValue, bool setCurrentValue = false) {
    if(nValue >= min_value && nValue <= max_value) {
        if(!setCurrentValue) {
            configuredValueByte = nValue;
        } else if (setCurrentValue) {
            * parameterByte = nValue;
            modified = true;
        }
    }
}

void SynthParameter::setValueFloat(float nValue, bool setCurrentValue = false) {
    if(nValue >= min_value && nValue <= max_value) {
        if(!setCurrentValue) {
            configuredValueFloat = nValue;
        } else if (setCurrentValue) {
            * parameterFloat = nValue;
            modified = true;
        }
    }
}

void SynthParameter::setValueBool(bool nValue, bool setCurrentValue = false) {
    if(!setCurrentValue) {
        configuredValueBool = nValue;
    } else if (setCurrentValue) {
        * parameterBool = nValue;
        modified = true;
    }
}

void SynthParameter::setValueEnum(int nValue, bool setCurrentValue = false) {
    if(nValue >= enumStartPosition && nValue < (enumStartPosition + enumAmount)) {
        if(!setCurrentValue) {
            configuredValueEnum = (SYNTH_P)nValue;
        } else if (setCurrentValue) {
            * parameterEnum = (SYNTH_P)nValue;
            modified = true;
        }
    }
}