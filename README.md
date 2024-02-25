Open source Esp32/Mozzi powered 3 oscillator substractive synth that fits in your pocket. Written for Arduino C++

Working:
- Synth core functionality
- UI
- Basic sequencer
- Envelopes
- Front panel STL
- Filters

WIP:
- Modulation
- Midi In (5 pin)

Next up:
- Effects
- Save/Load
- SD Card
- Back/Closure STL

WIP Photos:
![photo_2024-02-05_10-26-07](https://github.com/shaunEll/trSynth/assets/11801497/6fd74ba7-1d0b-42d8-87f1-3fca1ad30196)

![photo_2024-02-05_10-26-06](https://github.com/shaunEll/trSynth/assets/11801497/e9ad6a8e-7956-4e13-b23e-b0d213f6ebc7)

![photo_2024-02-05_10-26-06 (2)](https://github.com/shaunEll/trSynth/assets/11801497/dd9a2452-87be-46d0-a356-b74341eda70f)

![photo_2024-02-05_10-26-06 (3)](https://github.com/shaunEll/trSynth/assets/11801497/fcf431de-d757-40f8-8058-845abf4ce2dc)

BOM:
  - Esp32 Wroom module
  - PCM5102a I2S DAC
  - 2 KY-040 rotary encoders + 4 10K Resistors to 5v
  - 2 Momentary buttons
  - 2.8" TFT (Not touch) SPI screen
  - 3D Printing filament (I used PLA)
  - M2 & M3 screws and nuts
  - DIN Midi female connector
  - Midi input circuit components -> https://www.notesandvolts.com/2015/02/midi-and-arduino-build-midi-input.html


    
Libraries:
  - TFT_eSPI https://github.com/Bodmer/TFT_eSPI
  - Arduino MIDI https://github.com/FortySevenEffects/arduino_midi_library
  - Mozzi https://github.com/sensorium/Mozzi

NOTE: RTTI must be enabled for this to work