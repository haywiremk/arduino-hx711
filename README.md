# Arduino HX711 library for Mongoose OS

## Example code for JS
```
load('api_config.js');
load('api_events.js');
load('api_gpio.js');
load('api_mqtt.js');
load('api_net.js');
load('api_sys.js');
load('api_timer.js');
load('api_arduino_hx711.js');
let dataPin = 12;
let clkPin=14;

let sensor = HX711.init(dataPin, clkPin, 128);

// Blink built-in LED every second
GPIO.set_mode(led, GPIO.MODE_OUTPUT);
Timer.set(1000 /* 1 sec */, Timer.REPEAT, function() {
  let value = GPIO.toggle(led);
  print(value ? 'Tick' : 'Tock', 'uptime:', Sys.uptime(), getInfo());
  let value2 = sensor.read_average(4);
  print('HX711: ', value2);
}, null);
```
