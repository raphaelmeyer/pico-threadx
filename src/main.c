#include <hardware/gpio.h>
#include <pico/time.h>

uint power_led = PICO_DEFAULT_LED_PIN;

int main() {

  timer_hw->dbgpause = 0;

  gpio_init(power_led);
  gpio_set_dir(power_led, true);
  gpio_put(power_led, true);

  for (;;) {
    sleep_ms(250);
    gpio_put(power_led, false);
    sleep_ms(250);
    gpio_put(power_led, true);
  }
}
