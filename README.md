# Arduino Snippets

Library of useful C++ snippets and reusable classes I've created as I build out Arduino Uno and ESP32 projects.

## Button

A simple button utility that debounces and is meant to be triggered on `LOW` from a pin set to `INPUT_PULLUP`.


```cpp
// some data to send to action on press
int bData = ... 
 
void handleButton(void *data) {
  // Handle the button press
}
 
Button b(PIN, &bData, handleButton)
 
void loop() {
  b->test();
}
```

## Seven Segment

A utility for 4-digit seven segment displays using the TM1637 Drive Chip like [these](https://www.amazon.com/HiLetgo-Digital-Segment-Display-Arduino/dp/B01DKISMXK/ref=sr_1_1_sspa?dchild=1&keywords=tm1637&qid=1622991533&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExWUI0VUQ3OUFEMTUyJmVuY3J5cHRlZElkPUEwNTg2MzU4MTFQVjZCU0tTWTVVMiZlbmNyeXB0ZWRBZElkPUEwNTU2NTE3MjZJU042TldKOTM2RCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)

```cpp
#include "SevenSegment.h"

#define CLK 2
#define DIO 3

SevenSegment segment(CLK, DIO);

void onHalfSecond() {
  segment.clockPoint();
  
  // Set the hours and minutes from a clock source
  segment.setHours(clock.getHours());
  segment.setMinutes(clock.getMinutes());
  segment.update();
}

void setup() {
  segment.init();
  
  // Some kind of trigger on ever half-second
  // to flash the segment clock point
  // Timer1.initialize(500000); //timing for 500ms
  // Timer1.attachInterrupt(onHalfSecond);
}

void loop() {
  segment.loop();
}
```
