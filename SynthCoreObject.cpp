#include "SynthCoreObject.h"
 
SynthCoreObject::SynthCoreObject(String nName, int nId, SYNTH_MODULE_TYPE nType, bool isMod) {
  name = nName;
  indexId = nId;
  type = nType;
  modifier = isMod;
}

SynthCoreObject::SynthCoreObject(String nName, int nId, SYNTH_MODULE_TYPE nType, byte nParams, bool isMod) : 
  SynthCoreObject::SynthCoreObject(nName, nId, nType, isMod) {
  numParameters = nParams;
}

String SynthCoreObject::getName() { 
  return name; 
}

int SynthCoreObject::getIndex() { 
  return indexId; 
}

SYNTH_MODULE_TYPE SynthCoreObject::getModuleType() { 
  return type; 
}

bool SynthCoreObject::isModifier() { 
  return modifier; 
}

int SynthCoreObject::getNumParameters() { 
  return numParameters; 
}