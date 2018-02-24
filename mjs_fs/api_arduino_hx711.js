let HX711 = {
	
  _c_init: ffi('void *mgos_hx711_create(int, int, int)'),
  _c_read: ffi('int mgos_hx711_read(void *)'),
  _c_reada: ffi('int mgos_hx711_read_average(void *, int)'),
  _c_pd: ffi('void mgos_hx711_power_down(void *)'),
  _c_pu: ffi('void mgos_hx711_power_up(void *)'),
  _c_so: ffi('void mgos_hx711_set_offset(void *, int)'),
  _c_go: ffi('int mgos_hx711_get_offset(void *)'),
  _c_gv: ffi('int mgos_hx711_get_value(void *, int)'),
  _c_gu: ffi('int mgos_hx711_get_units(void *, int)'),
  _c_tare: ffi('void mgos_hx711_tare(void *, int)'),
  _c_ss: ffi('void mgos_hx711_set_scale(void *, int)'),
  _c_gs: ffi('int mgos_hx711_get_scale(void *)'),


  // Return value: an object with the methods described below.
  init: function(dout, pd_sck, gain) {
    let obj = Object.create(HX711._proto);
    // Initialize HX711 library.
    obj.hx = HX711._c_init(dout, pd_sck, gain);
    return obj;
  },
  
  _proto: {
    read: function() {
      return HX711._c_read(this.hx);
    },
	read_average: function(times) {
      return HX711._c_reada(this.hx, times);
    },
	power_down: function() {
      HX711._c_pd(this.hx);
    },
	power_up: function() {
      HX711._c_pu(this.hx);
    },
	set_offset: function(offset) {
      HX711._c_so(this.hx, offset);
    },
	get_offset: function() {
      HX711._c_go(this.hx);
    },
	get_value: function(times) {
      return HX711._c_gv(this.hx, times)  / 100.0;
    },
	get_units: function(times) {
      return HX711._c_gu(this.hx, times)  / 100.0;
    },
	tare: function(times) {
      HX711._c_tare(this.hx, times);
    },
	set_scale: function(scale) {
      HX711._c_ss(this.hx, scale);
    },
	get_scale: function() {
      return HX711._c_gs(this.hx)  / 100.0;
    },
		
  },
  
};