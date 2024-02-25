#include "SynthModMatrix.h"

SynthCoreModMatrix::SynthCoreModMatrix(SynthCoreObject * modules[], int numModules) {
    numConnections = 0;

    for(int x = 0; x < numModules; x++) {
        if(modules[x]->isModifier()) { 
            modifiers[numModifiers] = modules[x];
            numModifiers++;
        }

        for(int y = 0; y < modules[x]->getNumParameters(); y++) {
            params[(x * y) + y] = modules[x]->parameters[y];
            numParams++;    
        }
    }

    createDefaultConnection();
}

bool SynthCoreModMatrix::addConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue) {
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

byte SynthCoreModMatrix::getNumParameters() {
    return numParams;
}


void SynthCoreModMatrix::createDefaultConnection() {
    addConnection(modifiers[2],params[3], 50);
}