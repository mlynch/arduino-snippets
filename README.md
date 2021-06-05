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