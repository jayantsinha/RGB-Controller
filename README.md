# RGB-Controller
**A simple Arduino sketch to control WS2812B RGB LED strip.**

For any other LED module, just change the module identifier in 

`FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);`
