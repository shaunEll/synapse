#ifndef SynthCoreModMatrix_h
#define SynthCoreModMatrix_h

#include "SynthModifierObject.h"
#include "SynthCoreObject.h"
#include "SynthMatrixConnection.h"

#define MAX_CONNECTIONS 10
#define MAX_MODIFIERS 10
#define MAX_OBJECTS 20

class SynthCoreModMatrix {
    int initialValue;

    SynthMatrixConnection * connections[MAX_CONNECTIONS];
    byte numConnections = 0;     
    
    SynthModifierObject * modifiers[MAX_MODIFIERS];
    byte numModifiers = 0; 

    SynthCoreObject * coreObjects[MAX_OBJECTS];
    byte numObjects = 0;
    
    void createDefaultConnection();

    public:
        //######################### START MODMATRIX CLASS ################################
        SynthCoreModMatrix(SynthModifierObject * modules[], int numModules, SynthCoreObject * objects[], int numObjs);

        void updateModules(SynthModifierObject * modules[], int numModules, SynthCoreObject * objects[], int numObjs);
        
        bool addConnection(SynthModifierObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue);

        void editConnection(byte cNum, byte nPercentValue);

        void removeConnection(byte connectionNumber);

        String getConnectionString(byte cNum);

        byte getWetPercent(byte cNum);

        void processControl();

        void processUpdate();

        void resetValues();

        byte getNumConnections();

        byte getNumModifiers();

        byte getNumObjects();
};

#endif
