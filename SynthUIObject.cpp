#include "SynthUIObject.h"

SynthUIObject::SynthUIObject(SynthUICustomScreen * newScreen, String newName) {
    screen = newScreen;
    name = newName;

    custom = true;
}

SynthUIObject::SynthUIObject(SynthCoreObject * newObject) {
    module = newObject;
    numParameters = module->getNumParameters();

    for(int y = 0; y < numParameters; y++) {
        // if(dynamic_cast<SynthCoreObject::UISynthParameter*>(module->parameters[y]) != nullptr) {
        //     parameters[y] = dynamic_cast<SynthCoreObject::UISynthParameter*>(module->parameters[y]);
        // }
    }

    custom = false;
}

bool SynthUIObject::isCustomScreen() {
    return custom;
}

SYNTH_MODULE_TYPE SynthUIObject::getModuleType() {
    if(!custom) {
        return module->getModuleType();
    } else {
        return SYNTH_MODULE_TYPE::CUSTOM;
    }
}

String SynthUIObject::getName() {
    if(!custom) {
        return module->getName();
    }

    return name;
}

byte SynthUIObject::getNumParameters() {
    return numParameters;
}

void SynthUIObject::generateScreen(byte selectedParameter) {
    if(custom) {
        screen->generateScreen(selectedParameter);
    }
}

void SynthUIObject::increaseParameter(byte selectedParameter, bool shiftPressed) {
    if(custom) {
        screen->increaseParameter(selectedParameter, shiftPressed);
    } else {
        parameters[selectedParameter]->increaseParameter(shiftPressed);
    }
}

void SynthUIObject::decreaseParameter(byte selectedParameter, bool shiftPressed) {
    if(custom) {
        screen->decreaseParameter(selectedParameter, shiftPressed);
    } else {
        parameters[selectedParameter]->decreaseParameter(shiftPressed);
    }
}

void SynthUIObject::pressMultiButton(byte selectedParameter, bool shiftPressed) {
    if(custom) {
        screen->pressMultiButton(selectedParameter, shiftPressed);
    }
}
