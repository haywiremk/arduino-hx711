#include "Arduino.h"
#include "HX711.h"
#include "mgos_system.h"

/*
#if ARDUINO_VERSION <= 106
    // "yield" is not implemented as noop in older Arduino Core releases, so let's define it.
    // See also: https://stackoverflow.com/questions/34497758/what-is-the-secret-of-the-arduino-yieldfunction/34498165#34498165
    void yield(void) {};
#endif
*/
HX711::HX711(uint8_t dout, uint8_t pd_sck, uint8_t gain) {
	begin(dout, pd_sck, gain);
}


void HX711::begin(uint8_t dout, uint8_t pd_sck, uint8_t gain) {
	PD_SCK = pd_sck;
	DOUT = dout;

	pinMode(PD_SCK, OUTPUT);
	pinMode(DOUT, INPUT);

	set_gain(gain);
}

bool HX711::is_ready() {
	return digitalRead(DOUT) == LOW;
}

void HX711::set_gain(uint8_t gain) {
	switch (gain) {
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

	digitalWrite(PD_SCK, LOW);
	read();
}

int HX711::shiftIn(int dataPin, int clockPin, int bitOrder) {

 uint8_t value = 0;
 uint8_t i;

 for (i = 0; i < 8; ++i) {
	digitalWrite(clockPin, HIGH);
	mgos_usleep(1); //needed to meet chip spec
	 if (bitOrder == 0)
		value |= digitalRead(dataPin) << i;
	 else
		value |= digitalRead(dataPin) << (7 - i);

	 digitalWrite(clockPin, LOW);
	 mgos_usleep(1);//needed to meet chip spec
 }
 return value;
}

uint32_t HX711::read() {
	// wait for the chip to become ready
	while (!is_ready()) {
		// Will do nothing on Arduino but prevent resets of ESP8266 (Watchdog Issue)
		//yield();
	}

	uint32_t value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;
//rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
	// pulse the clock pin 24 times to read the data
	data[2] = shiftIn(DOUT, PD_SCK, 1);
	data[1] = shiftIn(DOUT, PD_SCK, 1);
	data[0] = shiftIn(DOUT, PD_SCK, 1);
//	rtc_clk_cpu_freq_set(RTC_CPU_FREQ_240M);

	// set the channel and the gain factor for the next reading using the clock pin
	for (unsigned int i = 0; i < GAIN; i++) {
		digitalWrite(PD_SCK, HIGH);
		digitalWrite(PD_SCK, LOW);
	}

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<unsigned uint32_t>(filler) << 24
			| static_cast<unsigned uint32_t>(data[2]) << 16
			| static_cast<unsigned uint32_t>(data[1]) << 8
			| static_cast<unsigned uint32_t>(data[0]) );

	return static_cast<uint32_t>(value);
}

uint32_t HX711::read_average(uint8_t times) {
	uint32_t sum = 0;
	for (byte i = 0; i < times; i++) {
		sum += read();
		//yield();
	}
	return sum / times;
}

double HX711::get_value(uint8_t times) {
	return read_average(times) - OFFSET;
}

float HX711::get_units(uint8_t times) {
	return get_value(times) / SCALE;
}

void HX711::tare(uint8_t times) {
	double sum = read_average(times);
	set_offset(sum);
}

void HX711::set_scale(float scale) {
	SCALE = scale;
}

float HX711::get_scale() {
	return SCALE;
}

void HX711::set_offset(uint32_t offset) {
	OFFSET = offset;
}

uint32_t HX711::get_offset() {
	return OFFSET;
}

void HX711::power_down() {
	digitalWrite(PD_SCK, LOW);
	digitalWrite(PD_SCK, HIGH);
}

void HX711::power_up() {
	digitalWrite(PD_SCK, LOW);
}