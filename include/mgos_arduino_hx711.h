/*
  * Arduino HX711 library API wrapper
 */

#ifndef CS_MOS_LIBS_ARDUINO_HX711_SRC_MGOS_ARDUINO_HX711_H_
#define CS_MOS_LIBS_ARDUINO_HX711_SRC_MGOS_ARDUINO_HX711_H_

#ifdef __cplusplus
#include "HX711.h"
#else
typedef struct HX711Tag HX711;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MGOS_HX711_RES_FAIL -10000

/*
 * Initialize HX711 library.
 */
HX711 *mgos_hx711_create(int dout, int pd_sck, int gain);

int mgos_hx711_read(HX711 *hx);
int mgos_hx711_read_average(HX711 *hx, int times);
void mgos_hx711_power_down(HX711 *hx);
void mgos_hx711_power_up(HX711 *hx);
void mgos_hx711_set_offset(HX711 *hx, int offset);
int mgos_hx711_get_offset(HX711 *hx);
int mgos_hx711_get_value(HX711 *hx, int times);
int mgos_hx711_get_units(HX711 *hx, int times);
void mgos_hx711_tare(HX711 *hx, int times);
void mgos_hx711_set_scale(HX711 *hx,int scale);
int mgos_hx711_get_scale(HX711 *hx);
	
#ifdef __cplusplus
}
#endif

#endif /* CS_MOS_LIBS_ARDUINO_HX711_SRC_MGOS_ARDUINO_HX711_H_ */