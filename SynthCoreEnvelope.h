#ifndef SynthCoreEnvelope_h
#define SynthCoreEnvelope_h

#include <MozziGuts.h>
#include <ADSR.h>

#include "SynthCoreObject.h"
#include "SynthModifierObject.h"

#define DEFAULT_ENV_DECAY_LEVELS 10
#define DEFAULT_ENV_ATTACK_LEVELS 255
#define DEFAULT_ENV_MS 5
#define DEFAULT_ENV_ATTACK 2
#define DEFAULT_ENV_DECAY 10
#define RESTART_ENV_ON_EDIT false

#define ENV_NUM_PARAMS 7

class SynthCoreEnvelope : public SynthCoreObject, public UpdatableParameterObject, public SynthModifierObject {
    ADSR <AUDIO_RATE, AUDIO_RATE> envelope;
    int envAttack, envDecay, envSustain, envRelease, nowValue;
    byte attackLevel, decayLevel;
    bool resetEnvelope = false;

    void setADSR(int atk, int decay, int sustain, int release );
    void setADLevels(byte atkLvl, byte decayLvl);

    public:
      SynthCoreEnvelope(String nName, int nId);

      void init() override;
      void processParameterUpdate(byte parameterID) override;

      //CONFIGURE
      void updateEnvelopeValues();

      //PLAYBACK
      void triggerNoteOn();
      void triggerNoteOff();

      //PROCESSING
      int updateEnvelope();

      //GET INFO
      int getValue();
      bool isPlaying();
      bool getEnvelopeReset();

      //MODIFIER
      int getModifierValueInt() override;
      float getModifierValueFloat() override;
      byte getModifierValueByte() override;
      bool getModifierValueBool() override;

      void copyObject(SynthCoreObject * obj) override;        
};

#endif