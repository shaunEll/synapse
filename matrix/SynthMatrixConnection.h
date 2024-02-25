#ifndef SynthMatrixConnection_h
#define SynthMatrixConnection_h

#define DEFAULT_WET_PERCENT 50

class SynthCoreObject;
class SynthParameter;

class SynthMatrixConnection {
    SynthCoreObject * modSource;
    SynthParameter * targetParam;
    byte percentValue;

    public:
        SynthMatrixConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam, byte nPercentValue);
        SynthMatrixConnection(SynthCoreObject * nModSource, SynthParameter * nTargetParam);

        int getModValueInt();
        int getModValueByte();

        void processConnectionUpdate();
        void processConnectionControl();
        void restoreOriginalValue();
        void updateWetPercent(byte newWet);
        byte getWetPercent();
        String toString();
};

#endif