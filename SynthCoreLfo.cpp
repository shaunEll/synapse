#include "SynthCoreLfo.h"

SynthCoreLFO::SynthCoreLFO(String nName, int nId) : SynthCoreObject(nName, nId, SYNTH_MODULE_TYPE::LFO, LFO_NUM_PARAMS, true), SynthModifierObject(nName) {
    parameters[0] = new SynthParameter("Waveform", 0, nName, &lfoShape, LFO_START_POSITION, LFO_WAVEFORMS, this);
    parameters[1] = new SynthParameter("Frequency", 1, nName, &lfoFrequency, 0.1f, -200, 200, this);

    init(); 
}

void SynthCoreLFO::init() {
    lfoFrequency = DEFAULT_LFO_FREQUENCY;

    setLFOShape(SYNTH_P::LFO_SINE);
    updateFrequency();
}

void SynthCoreLFO::processParameterUpdate(byte parameterID) {
  if(parameterID == 0) {
    setLFOShape(lfoShape);
  } else {
    updateFrequency();
  }
}

void SynthCoreLFO::setLFOShape(SYNTH_P lfoType) {
    lfoShape = lfoType;

    switch(lfoType){
        case (SYNTH_P::LFO_SINE):
            lfo.setTable(SIN8192_DATA);
            break;
        case (SYNTH_P::LFO_SAW):
            lfo.setTable(SAW8192_DATA);
            break;
        case (SYNTH_P::LFO_TRIANGLE):
            lfo.setTable(TRIANGLE_WARM8192_DATA);
            break;
        case (SYNTH_P::LFO_SQUARE):
            lfo.setTable(SMOOTHSQUARE8192_DATA);
            break;
        case (SYNTH_P::LFO_WHITENOISE):
            lfo.setTable(WHITENOISE8192_DATA);
            break;
        default:
          break;
    }
}

float SynthCoreLFO::process() {
    lfoValue = lfo.next();
    return lfoValue;
}

void SynthCoreLFO::restartLFO(){
    lfo.setPhase(0);
}

float SynthCoreLFO::getModifierValueFloat() {
    return lfoValue;
}

int SynthCoreLFO::getModifierValueInt() {
    return (int)lfoValue;
}

byte SynthCoreLFO::getModifierValueByte() {
    return (byte)(map(lfoValue,-255,255,0,255));
}

bool SynthCoreLFO::getModifierValueBool() {
    return (bool)(map(lfoValue,-255,255,0,1));
}

void SynthCoreLFO::updateFrequency() {
    lfo.setFreq(lfoFrequency);
}

void SynthCoreLFO::copyObject(SynthCoreObject * obj) {

}
