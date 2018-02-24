#include <math.h>
#include "mgos_arduino_hx711.h"

HX711 *mgos_hx711_create(int dout, int pd_sck, int gain) {
	return new HX711(dout, pd_sck, gain);
}


int mgos_hx711_read(HX711 *hx) {
	if (hx == nullptr) return 0;
	return hx->read();
}

int mgos_hx711_read_average(HX711 *hx, int times) {
	if (hx == nullptr) return 0;
	return hx->read_average(times);
}

void mgos_hx711_power_down(HX711 *hx) {
	if (hx == nullptr) return;
	hx->power_down();
}

void mgos_hx711_power_up(HX711 *hx) {
	if (hx == nullptr) return;
	hx->power_up();
}

void mgos_hx711_set_offset(HX711 *hx, int offset) {
	if (hx == nullptr) return;
	hx->set_offset(offset);
}

int mgos_hx711_get_offset(HX711 *hx) {
	if (hx == nullptr) return 0;
	return hx->get_offset();
}

int mgos_hx711_get_value(HX711 *hx, int times) {
	if (hx == nullptr) return 0;
	return round(hx->get_value(times) * 100.0);
}

int mgos_hx711_get_units(HX711 *hx, int times) {
	if (hx == nullptr) return 0;
	return round(hx->get_units(times) * 100.0);
}

void mgos_hx711_tare(HX711 *hx, int times) {
	if (hx == nullptr) return;
	hx->tare(times);
}

void mgos_hx711_set_scale(HX711 *hx,int scale) {
	if (hx == nullptr) return;
	hx->set_scale(scale);
}

int mgos_hx711_get_scale(HX711 *hx) {
	if (hx == nullptr) return 0;
	return round(hx->get_scale() * 100.0);
}