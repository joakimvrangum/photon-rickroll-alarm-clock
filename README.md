# :alarm_clock: Rickroll alarm clock - Particle Photon + Android app

A Particle Photon powered physical alarm clock that plays _**Rick Astley - Never Gonna Give You Up**_, until you get out of bed, and within 75mm of the ultrasonic sensor. Alarm is set from an Android app.
This was my take on an assignments in Embedded Systems, _spring 2018_.

### Requirements
##### Hardware
- Particle Photon (Wifi-enabled dev-kit)
- TFT display (1.8", ST7735)
- HC-SR04 ultrasonic sensor
- piezo buzzer

##### Software
- Particle Dev (desktop or cli)
    - for flushing to Photon device
- AdafruitST7735 lib
    - should already be set in project, but import manually if errors occur

**Also requires an account with Particle.io for their API features.**

### Hardware diagram

Attached is a hardware wire diagram, made with Fritzing.
![Alt Text](assets/hw_diagram_fzz.jpg?raw=true, "Fritzing diagram")

### Particle Photon

Uses Photon's built in RTC (Real Time Clock). It has one dependancy - **AdafruitST7735** - a library to help get the TFT-screen working. I wrote a simple wrapper for it in **tft_screen.cpp**. I wrote separate libraries for most of the functionality, but they are hardly general purpose libs, so only really serves this purpose.

### Android app

The Android app is incredibly basic, and is only meant as a simple proof-of-concept.
It communicates with the Particle Cloud API, so you would need to alter the lines
that sends the requests to their API, stating your own **_device id_** and **_access token_**.
I have not refactored the code, and will only bother doing so if I find the need to make a similar
app in the future.
I have omitted the all gradle, ide, properties and build files, so I suggest making a new project in Android Studio and experimenting when importing the code. Should be fairly simple if familiar with Android development, or Java.

### Video demo

<a href="https://youtu.be/KZkot4DFyu4
" target="_blank"><img src="http://img.youtube.com/vi/KZkot4DFyu4/0.jpg"
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

### Resources and links
![SPI vs hard-wiring](http://maxembedded.com/2013/11/the-spi-of-the-avr)

![Adafruit ST7735 lib](https://github.com/adafruit/Adafruit-ST7735-Library/)

![Youtube- Rick Astley - Never Gonna Give You Up](https://www.youtube.com/watch?v=dQw4w9WgXcQ)

![Particle Community - ST7735 not working..](https://community.particle.io/t/tft-display-1-8-st7735-not-working-with-particle-photon/37655/2)
