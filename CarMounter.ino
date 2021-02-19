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

UpDownSwitch upDownSwitch(2, 3);

Led blueLed(7);
Led redLed(8);

MagnetSwitch magnetSwitch(12);

void setup() {
	Serial.begin(9600);
	digitalWrite(LED_BUILTIN, LOW);
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

	delay(500);
}