#ifndef SynthCoreFilter_h
#define SynthCoreFilter_h

#include "Arduino.h" 
#include <MozziGuts.h>

#include "SynthCoreObject.h"

//FILTERS
#include <LowPassFilter.h>
#include <ResonantFilter.h>
#include <StateVariable.h>

//FILTER DEFINES
#define FILTER_NUM_PARAMS 3
#define NUM_FILTER_TYPES 3
#define FILTER_PARAMS_START 9

#define MAX_RESONANCE 255

#define FREQUENCY_DEFAULT 20
#define RESONANCE_DEFAULT 0

#define RESONANCE_MULTIPLIER 5
#define FREQUENCY_MULTIPLIER 5

#define FILTER_SHIFT_FACTOR 5

class SynthCoreFilter : public SynthCoreObject, public UpdatableParameterObject  {
    SYNTH_P filterType;

    ResonantFilter <LOWPASS> lpf;
    StateVariable <BANDPASS> bpf;
    StateVariable <HIGHPASS> hpf;

    int cutoffFrequency;
    int resonance;

    public:
        SynthCoreFilter(String nName, int nId);

        void init() override;
        void processParameterUpdate(byte parameterID) override;

        void setFilterType(SYNTH_P filType);
        void updateFilterValues();

        int applyFilter(int filterInput);

        void copyObject(SynthCoreObject * obj) override; 
};



#endif