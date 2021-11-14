#include "SevSegShift.h"

class LedSegment : public SevSegShift {

public:
	LedSegment(int ds_pin, int shcp_pin, int stcp_pin, byte *four_digit_pins, byte *eight_segment_pins) : SevSegShift(ds_pin, shcp_pin, stcp_pin, 1, true) {
		this->begin(COMMON_CATHODE, 4, four_digit_pins, eight_segment_pins, false, false, false, false);
	}
};

class UpDownSwitch {

private:
	int upPin;
	int downPin;

public:
	UpDownSwitch(int digital_up_pin, int digital_down_pin) {
		this->upPin = digital_up_pin;
		this->downPin = digital_down_pin;

		pinMode(this->upPin, INPUT_PULLUP);
		pinMode(this->downPin, INPUT_PULLUP);
	}

	bool isUp() { return digitalRead(this->upPin) == LOW; }
	bool isDown() { return digitalRead(this->downPin) == LOW; }
	bool isOff() { return !isUp() && !isDown(); }
};

class Led {

private:
	int pin;

public:
	Led(int digital_pin) {
		this->pin = digital_pin;

		pinMode(this->pin, OUTPUT);
	}

	void on() { digitalWrite(this->pin, HIGH); }
	void off() { digitalWrite(this->pin, LOW); }
};

class MagnetSwitch {

private:
	int pin;

public:
	MagnetSwitch(int digital_pin) {
		this->pin = digital_pin;

		pinMode(this->pin, INPUT_PULLUP);
	}

	bool isOpen() { return digitalRead(this->pin) == HIGH; }
	bool isClosed() { return !isOpen(); }
};

LedSegment ledSegment(8, 9, 10, new byte[4]{7, 6, 5, 4}, new byte[8]{0, 1, 4, 6, 7, 2, 3, 5});

UpDownSwitch upDownSwitch(2, 3);

MagnetSwitch magnetSwitch(11);

Led blueLed(12);
Led redLed(13);

void setup() {
	Serial.begin(115200);
	digitalWrite(LED_BUILTIN, LOW);

	ledSegment.setNumber(3141, 3); 
}

void loop() {

	if (magnetSwitch.isClosed()) {
		redLed.off();
		blueLed.off();
	} else {

		if (upDownSwitch.isUp()) {
			Serial.println("Up");
			blueLed.on();
			redLed.off();
		} else if (upDownSwitch.isDown()) {
			Serial.println("Down");
			redLed.on();
			blueLed.off();
		} else {
			Serial.println("Off");
			redLed.off();
			blueLed.off();
		}
	}

	ledSegment.refreshDisplay();
}
