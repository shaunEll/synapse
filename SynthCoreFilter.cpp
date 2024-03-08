#include "SynthCoreFilter.h"

SynthCoreFilter::SynthCoreFilter(String nName, int nId) : SynthCoreObject(nName, nId, SYNTH_MODULE_TYPE::FILTER, FILTER_NUM_PARAMS, false) {
    parameters[0] = new SynthParameter("Type", 0, nName, &filterType, FILTER_PARAMS_START, NUM_FILTER_TYPES, nullptr);
    parameters[1] = new SynthParameter("Frequency", 1, nName, &cutoffFrequency, 5, 0, 40000, this);
    parameters[2] = new SynthParameter("Resonance", 2, nName, &resonance, 1, 0, 250, this);

    init();
}

void SynthCoreFilter::init() {
    lpf.setCutoffFreqAndResonance(FREQUENCY_DEFAULT, RESONANCE_DEFAULT);
    hpf.setResonance(RESONANCE_DEFAULT);
    hpf.setCentreFreq(FREQUENCY_DEFAULT);
    bpf.setResonance(RESONANCE_DEFAULT);
    bpf.setCentreFreq(FREQUENCY_DEFAULT);

    cutoffFrequency = FREQUENCY_DEFAULT;
    resonance = RESONANCE_DEFAULT;

    setFilterType(SYNTH_P::FILTER_LOWPASS);
}

void SynthCoreFilter::setFilterType(SYNTH_P filType) {
    filterType = filType;
}

int SynthCoreFilter::applyFilter(int filterInput) {
    switch (filterType) {
        case SYNTH_P::FILTER_LOWPASS:
            return lpf.next(filterInput);
            break;
        case SYNTH_P::FILTER_HIGHPASS:
            return hpf.next(filterInput);
            break;
        case SYNTH_P::FILTER_BANDPASS:
            return bpf.next(filterInput);
            break;
        default:
            return filterInput; //Unfiltered sound
            break;
    }
}

void SynthCoreFilter::processParameterUpdate(byte parameterID) {
  updateFilterValues();
}

void SynthCoreFilter::updateFilterValues() {
    lpf.setCutoffFreqAndResonance(cutoffFrequency,resonance);

    hpf.setResonance(resonance);
    hpf.setCentreFreq(cutoffFrequency);

    hpf.setResonance(resonance);
    hpf.setCentreFreq(cutoffFrequency);
}

void copyObject(SynthCoreObject * obj) {
  
}