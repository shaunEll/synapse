#include "SynthCoreEnvelope.h"

void SynthCoreEnvelope::setADSR(int atk, int decay, int sustain, int release ) {
  envAttack = atk;
  envDecay = decay;
  envSustain = sustain;
  envRelease = release;

  envelope.setTimes(envAttack,envDecay,envSustain,envRelease);
}

void SynthCoreEnvelope::setADLevels(byte atkLvl, byte decayLvl) {
  attackLevel = atkLvl;
  decayLevel = decayLvl;

  envelope.setADLevels(atkLvl,decayLvl);
}

SynthCoreEnvelope::SynthCoreEnvelope(String nName, int nId) : SynthCoreObject(nName, nId, SYNTH_MODULE_TYPE::ENVELOPE, ENV_NUM_PARAMS, true), SynthModifierObject(nName) {
    parameters[0] = new SynthParameter("Attack", 0, nName, &envAttack, 1, 0, 100000, this);
    parameters[1] = new SynthParameter("Decay", 1, nName, &envDecay, 1, 0, 100000, this);
    parameters[2] = new SynthParameter("Sustain", 2, nName, &envSustain, 1, 0, 100000, this);
    parameters[3] = new SynthParameter("Release", 3, nName, &envRelease, 1, 0, 100000, this);
    parameters[4] = new SynthParameter("Attack Lvl", 4, nName, &attackLevel, 1, 0, 255, this);
    parameters[5] = new SynthParameter("Decay Lvl", 5, nName, &decayLevel, 1, 0, 255, this);
    parameters[6] = new SynthParameter("Reset", 6, nName, &resetEnvelope, nullptr);

    init();
}

void SynthCoreEnvelope::init() {
    envAttack = DEFAULT_ENV_ATTACK;
    envDecay = DEFAULT_ENV_DECAY;
    envSustain = DEFAULT_ENV_MS;
    envRelease = DEFAULT_ENV_MS;
    attackLevel = DEFAULT_ENV_ATTACK_LEVELS;
    decayLevel = DEFAULT_ENV_DECAY_LEVELS;

    updateEnvelopeValues();
}

void SynthCoreEnvelope::processParameterUpdate(byte parameterID) {
  updateEnvelopeValues();
}

//CONFIGURE
void SynthCoreEnvelope::updateEnvelopeValues() {
    setADSR(envAttack,envDecay,envSustain,envRelease);
    setADLevels(attackLevel,decayLevel);
}

//PLAYBACK
void SynthCoreEnvelope::triggerNoteOn() {
    envelope.noteOn(resetEnvelope);
}

void SynthCoreEnvelope::triggerNoteOff() {
    envelope.noteOff();
}

//PROCESSING
int SynthCoreEnvelope::updateEnvelope() {
    envelope.update();
    nowValue = envelope.next();

    return nowValue;
}

//GET INFO
int SynthCoreEnvelope::getValue() {
    return nowValue;
}

int SynthCoreEnvelope::getModifierValueInt() {
    return nowValue;
}

float SynthCoreEnvelope::getModifierValueFloat() {
    return (float)nowValue;
}

byte SynthCoreEnvelope::getModifierValueByte() {
    return (byte)nowValue;
}

bool SynthCoreEnvelope::getModifierValueBool() {
    return (bool)(map(nowValue,0,255,0,1));
}

bool SynthCoreEnvelope::isPlaying() {
    return envelope.playing();
}

bool SynthCoreEnvelope::getEnvelopeReset() {
    return resetEnvelope;
}

void SynthCoreEnvelope::copyObject(SynthCoreObject * obj) {
  if(obj->getModuleType() == getModuleType()) {
        //SynthCoreEnvelope * sourceObject = ((SynthCoreEnvelope *)obj);
    }
}  