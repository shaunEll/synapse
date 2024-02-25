#ifndef SynthCoreModMatrix_h
#define SynthCoreModMatrix_h

#include "Arduino.h"
#include "../core/SynthCoreObject.h"
#include "SynthMatrixConnection.h"

#define MAX_CONNECTIONS 10
#define MAX_MODIFIERS 5

class SynthCoreModMatrix {
    int initialValue;

    SynthMatrixConnection * connections[MAX_CONNECTIONS];
    byte numConnections = 0;     
    
    SynthCoreObject * modifiers[MAX_MODIFIERS];
    byte numModifiers = 0; 

    SynthParameter * params[50];
    byte numParams = 0;
    
    void createDefaultConnection();

    public:
        //######################### START MODMATRIX CLASS ################################
        SynthCoreModMatrix(SynthCoreObject * modules[], int numModules);

        bool addConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue);

        void editConnection(byte cNum, byte nPercentValue);

        void removeConnection(byte connectionNumber);

        String getConnectionString(byte cNum);

        byte getWetPercent(byte cNum);

        void processControl();

        void processUpdate();

        void resetValues();

        byte getNumConnections();

        byte getNumModifiers();

        byte getNumParameters();
};

#endif
