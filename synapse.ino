//#include "MozziGuts.h"

#include "SynthCoreOsc.h"
#include "SynthCoreEnvelope.h"
#include "SynthModMatrix.h"

SynthCoreOsc * osc = new SynthCoreOsc("Osc 1", 0);
SynthCoreEnvelope * env = new SynthCoreEnvelope("Env 1", 1);

SynthCoreObject * objs[2] = { (SynthCoreObject *)osc, (SynthCoreObject *)env };
SynthModifierObject * mods[1] = { (SynthModifierObject *)env };

SynthCoreModMatrix * matrix = new SynthCoreModMatrix(mods,1,objs,2);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
