#include "SynthCoreOsc.h"

SynthCoreOsc::SynthCoreOsc(String nName, int nId) : SynthCoreObject(nName, nId, SYNTH_MODULE_TYPE::OSCILLATOR, OSC_NUM_PARAMS, false) {
    parameters[0] = new SynthParameter("Enabled", 0, nName, &isEnabled,nullptr);
    parameters[1] = new SynthParameter("Waveform", 1, nName, &oscillatorShape, SYNTH_P_OSC_START, SYNTH_P_OSC_LENGTH, this); 
    parameters[2] = new SynthParameter("Volume", 2, nName, &volumeLevel, 1, 0, 255, nullptr);
    parameters[3] = new SynthParameter("Pitch", 3, nName, &tuning, 1, -96, 96, this);
    parameters[4] = new SynthParameter("Detune", 4, nName, &detune, 1, -1000, 1000, this);
    parameters[5] = new SynthParameter("Phase", 5, nName, &phase, 0.1f, -1.0f, 1.0f, this);

    init();
}

void SynthCoreOsc::processParameterUpdate(byte parameterID) {
    if (parameterID == 1) {
        setOscillatorShape();
    } else if (parameterID == 3 || parameterID == 4 || parameterID == 5) {
        setCurrentNote();
    }
}

void SynthCoreOsc::init() {
    oscillatorShape = SYNTH_P::OSC_SINE;
    setOscillatorShape();

    setNote(OSC_BASE_MIDI_NOTE);
    setInitVolumeLevel();
    setPhase(0);
    setDetune(0);
    setTuning(0);
    setEnabled(false);
}

int SynthCoreOsc::process(){
    return (int) (voice.next() * velocity) >> 2;
}

void SynthCoreOsc::toggleEnabled() {
    isEnabled = !isEnabled;
}

void SynthCoreOsc::setEnabled(bool newState) {
    isEnabled = newState;
}

bool SynthCoreOsc::enabled() {
    return isEnabled;
}

//OSC SHAPE
void SynthCoreOsc::setOscillatorShape() {
    switch(oscillatorShape){
        case (SYNTH_P::OSC_SINE):
            voice.setTable(SIN8192_DATA);
            break;
        case (SYNTH_P::OSC_SAW):
            voice.setTable(SAW8192_DATA);
            break;
        case (SYNTH_P::OSC_TRIANGLE):
            voice.setTable(TRIANGLE_WARM8192_DATA);
            break;
        case (SYNTH_P::OSC_SQUARE):
            voice.setTable(SMOOTHSQUARE8192_DATA);
            break;
        case (SYNTH_P::OSC_WHITENOISE):
            voice.setTable(WHITENOISE8192_DATA);
            break;
        case (SYNTH_P::OSC_CHUM78):
            voice.setTable(CHUM78_DATA);
            break;
        case (SYNTH_P::OSC_SQ2):
            voice.setTable(SQUARE_NO_ALIAS_2048_DATA);
            break;
        case (SYNTH_P::OSC_TR2):
            voice.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
            break;
        default:
            break;
    }
}

void SynthCoreOsc::setOscillatorShape(SYNTH_P oscType) {
    oscillatorShape = oscType;
    setOscillatorShape();
}

SYNTH_P SynthCoreOsc::getOscillatorShape() {
    return oscillatorShape;
}

//VOLUMES
void SynthCoreOsc::setInitVolumeLevel() {
    volumeLevel = OSC_INIT_VOLUME;
}

bool SynthCoreOsc::setVolume(byte newVolume) {
    if(newVolume >= 0 && newVolume <= OSC_MAX_VOLUME){
        volumeLevel = newVolume;
        return true;
    }
    return false;
}

byte SynthCoreOsc::getVolume() {
    return volumeLevel;
}

byte SynthCoreOsc::getDefaultVelocity() {
    return OSC_DEFAULT_VELOCITY;
}

//NOTES/FREQUENCY
void SynthCoreOsc::setNote(int midiNote, byte newVelocity) {     
    currentNote = midiNote;     
    float tunedNote = mtof(midiNote + tuning) + detune;

    voice.setFreq(tunedNote);
    //voice.setVelocity(newVelocity); -- DISABLED BECAUSE IT CAUSED CLICKING
}

void SynthCoreOsc::setNote(int midiNote) {     
    setNote(midiNote, getDefaultVelocity());
}

void SynthCoreOsc::setCurrentNote() {
    setNote(currentNote);
}

void SynthCoreOsc::playNote(int midiNote) {      //BACKWARDS COMPATIBILITY
    setNote(midiNote);
}

void SynthCoreOsc::setTuning(int newTuning) {
    tuning = newTuning;
    setNote(currentNote);
}

int SynthCoreOsc::getTuning() {
    return tuning;
}

void SynthCoreOsc::setDetune(int newDetune) {
    detune = newDetune;
    setNote(currentNote);
}

int SynthCoreOsc::getDetune() {
    return detune;
}

//PHASE
void SynthCoreOsc::setPhase(int newPhase) {
    phase = newPhase;

    voice.setPhase(phase);
}

float SynthCoreOsc::getPhase() {
    return phase;
}

void SynthCoreOsc::copyObject(SynthCoreObject * obj) {
    if(obj->getModuleType() == getModuleType()) {
        SynthCoreOsc * sourceObject = ((SynthCoreOsc*)obj);

        setEnabled(sourceObject->enabled());
        setOscillatorShape(sourceObject->getOscillatorShape());
        setTuning(sourceObject->getTuning());
        setDetune(sourceObject->getDetune());
        setPhase(sourceObject->getPhase());
        setVolume(sourceObject->getVolume());
    }
}