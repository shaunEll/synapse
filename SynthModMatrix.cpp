#include "SynthModMatrix.h"

SynthCoreModMatrix::SynthCoreModMatrix(SynthModifierObject * modules[], int numModules, SynthCoreObject * objects[], int numObjs) {
    updateModules(modules, numModules, objects, numObjs);
    
    numConnections = 0;
    createDefaultConnection();
}

void SynthCoreModMatrix::updateModules(SynthModifierObject * modules[], int numModules, SynthCoreObject * objects[], int numObjs) {
  numModifiers = 0;
  numObjects = 0;

  for(int x = 0; x < numModules; x++) {
      modifiers[numModifiers] = modules[x];
      numModifiers++;
    }

    for(int x = 0; x < numObjs; x++) {
      coreObjects[numObjects] = objects[x];
      numObjects++;
    }
}

bool SynthCoreModMatrix::addConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue) {
    if (numConnections < MAX_CONNECTIONS) {
        connections[numConnections] = new SynthMatrixConnection(nModSource, nTargetParam, nPercentValue);
        numConnections++;

        return true;
    }

    return false;
}

void SynthCoreModMatrix::editConnection(byte cNum, byte nPercentValue) {
    if(cNum < numConnections) {
        connections[cNum]->updateWetPercent(nPercentValue); 
    }
}

void SynthCoreModMatrix::removeConnection(byte connectionNumber) {
    if(connectionNumber < numConnections) {
        for(int x = connectionNumber; x < numConnections; x++) {
            connections[x] = connections[x + 1];
        }

        numConnections--;
    }
}

String SynthCoreModMatrix::getConnectionString(byte cNum) {
    if(cNum < numConnections) {
        return connections[cNum]->toString();
    }

    return "(empty)";
}

byte SynthCoreModMatrix::getWetPercent(byte cNum) {
    if(cNum < numConnections) {
        return connections[cNum]->getWetPercent();
    }

    return 0;
}

void SynthCoreModMatrix::processControl() {
    for(int x = 0; x < numConnections; x++) {
        connections[x]->processConnectionControl();
    }
}

void SynthCoreModMatrix::processUpdate() {
    for(int x = 0; x < numConnections; x++) {
        connections[x]->processConnectionUpdate();

    }        
}

void SynthCoreModMatrix::resetValues() {
    for(int x = 0; x < numConnections; x++) {
        connections[x]->restoreOriginalValue();
    }
}

byte SynthCoreModMatrix::getNumConnections() {
    return numConnections;
}

byte SynthCoreModMatrix::getNumModifiers() {
    return numModifiers;
}

byte SynthCoreModMatrix::getNumObjects() {
    return numObjects;
}

void SynthCoreModMatrix::createDefaultConnection() {
    addConnection(modifiers[0],coreObjects[0]->parameters[2], 50);
}