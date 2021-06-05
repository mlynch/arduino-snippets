/**
 * Simple Button utility with built-in debouncing.
 * 
 * Usage:
 * 
 * // some data to send to action on press
 * int bData = ... 
 * 
 * void handleButton(void *data) {
 *   // Handle the button press
 * }
 * 
 * Button b(PIN, &bData, handleButton)
 * 
 * void loop() {
 *    b->test();
 * }
 */

// ms to sample button state
#define BUTTON_DEBOUNCE 20

typedef void * ButtonData;

class Button {
  int debounceDelay = BUTTON_DEBOUNCE;

  int currentValue;
  int tempValue;

  unsigned long lastTime = 0;

  int currentPin;
  ButtonData data;
  void (*action)(ButtonData data);

  public:
  Button(int pin, ButtonData data, void (*action)(ButtonData data), bool onRise = false) {
    this->currentPin = pin;
    this->data = data;
    this->action = action;
  }

  int read() {
    this->tempValue = digitalRead(this->currentPin);
    return this->tempValue;
  }

  int value() {
    return this->currentValue;
  }

  void pushed() {
    this->currentValue = 1;
    this->lastTime = millis();
    this->action(this->data);
  }

  void clear() {
    this->currentValue = 0;
    this->lastTime = millis();
  }

  int pin() {
    return this->currentPin;
  }

  bool ready() {
    return (millis() - this->lastTime) > this->debounceDelay;
  }

  void test() {
    int buttonRead = this->read();
    if (this->ready()) {
      if (buttonRead == LOW && this->value() == 0) {
        this->pushed();
      } else if (buttonRead == HIGH && this->value() == 1) {
        this->clear();
      }
    }
  }
};
