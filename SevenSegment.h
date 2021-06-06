/**
 * 4-digit seven segment display using TM1637 controller
 */
#include "TM1637.h"

class SevenSegment {
  bool showClockPoint = false;
  bool shouldUpdate = true;

  int8_t timeDisp[4];// = {0x00,0x00,0x00,0x00};

  TM1637 *tm1637;

  unsigned char hours = 0;
  unsigned char minutes = 0;

  public:
  SevenSegment(uint8_t clkPin, uint8_t dioPin) {
    tm1637 = new TM1637(clkPin, dioPin);

    timeDisp[0] = 0x00;
    timeDisp[1] = 0x00;
    timeDisp[2] = 0x00;
    timeDisp[3] = 0x00;
  }

  void init() {
    tm1637->set();
    tm1637->init();
  }

  void loop() {
    if(this->shouldUpdate) {
      this->draw();
      this->tm1637->display(this->timeDisp);
    }
  }

  void update() {
    this->shouldUpdate = true;
  }

  void setMinutes(unsigned char minutes) {
    this->minutes = minutes;
  }

  void setHours(unsigned char hours) {
    this->hours = hours;
  }

  void setClockPoint(bool showClockPoint) {
    this->showClockPoint = showClockPoint;
  }

  void clockPoint() {
    this->showClockPoint = !this->showClockPoint;
  }

  void draw() {
    if (this->showClockPoint) {
      this->tm1637->point(POINT_ON);
    } else {
      this->tm1637->point(POINT_OFF);
    }

    this->timeDisp[0] = this->hours / 10;
    this->timeDisp[1] = this->hours % 10;
    this->timeDisp[2] = this->minutes / 10;
    this->timeDisp[3] = this->minutes % 10;

    this->shouldUpdate = false;
  }
};