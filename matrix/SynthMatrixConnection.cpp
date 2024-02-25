#include "SynthMatrixConnection.h"
#include "../core/SynthCoreObject.h"

SynthMatrixConnection::SynthMatrixConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue) {
    modSource = nModSource;
    targetParam = nTargetParam;
    percentValue = nPercentValue;
}

SynthMatrixConnection::SynthMatrixConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam) : 
    SynthMatrixConnection(nModSource, nTargetParam, DEFAULT_WET_PERCENT) {
}

void SynthMatrixConnection::processConnectionUpdate() {
    targetParam->process();
}

int SynthMatrixConnection::getModValueInt() {
    return * modSource->getModifierValueInt();
}

int SynthMatrixConnection::getModValueByte() {
    return * modSource->getModifierValueByte();
}

void SynthMatrixConnection::processConnectionControl() {
    targetParam->applyModifier(this, true);
        
}

void SynthMatrixConnection::restoreOriginalValue() {
    targetParam->resetState();
}

void SynthMatrixConnection::updateWetPercent(byte newWet) {
    if(newWet <= 100) {
        percentValue = newWet;
    } else {
        percentValue = 100;
    }
}

byte SynthMatrixConnection::getWetPercent() {
    return percentValue;
}

String SynthMatrixConnection::toString() {
    return String(modSource->getName()) + " > " + percentValue + "% > " + String(targetParam->getParentName()) + "." + (targetParam->getNameShort()) ;
}