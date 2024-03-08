#include "SynthMatrixConnection.h"
#include "SynthModifierObject.h"
#include "SynthParameter.h"

SynthMatrixConnection::SynthMatrixConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue) {
    modSource = nModSource;
    targetParam = nTargetParam;
    percentValue = nPercentValue;
}

SynthMatrixConnection::SynthMatrixConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam) : 
    SynthMatrixConnection(nModSource, nTargetParam, DEFAULT_WET_PERCENT) {
}

void SynthMatrixConnection::processConnectionUpdate() {
    targetParam->process();
}

int SynthMatrixConnection::getModValueInt() {
    return modSource->getModifierValueInt();
}

byte SynthMatrixConnection::getModValueByte() {
    return modSource->getModifierValueByte();
}

float SynthMatrixConnection::getModValueFloat(){
  return modSource->getModifierValueFloat();
}

bool SynthMatrixConnection::getModValueBool(){
  return modSource->getModifierValueBool();
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
    return String(modSource->getModifierName()) + " > " + percentValue + "% > " + String(targetParam->getParentName()) + "." + (targetParam->getNameShort()) ;
}