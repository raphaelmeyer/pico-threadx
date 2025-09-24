#include <tx_api.h>

#include <hardware/gpio.h>
#include <pico/time.h>

uint power_led = PICO_DEFAULT_LED_PIN;

TX_BYTE_POOL byte_pool;

TX_THREAD blink;

TX_THREAD producer;
TX_THREAD consumer;
TX_SEMAPHORE stuff;

uint8_t byte_pool_buffer[8192];

int main() {

  timer_hw->dbgpause = 0;

  gpio_init(power_led);
  gpio_set_dir(power_led, true);
  gpio_put(power_led, true);

  tx_kernel_enter();
}

static void blink_main(uint32_t input) {
  for (;;) {
    tx_thread_sleep(25);
    gpio_put(power_led, false);
    tx_thread_sleep(25);
    gpio_put(power_led, true);
  }
}

static void producer_main(uint32_t input) {
  for (;;) {
    tx_semaphore_put(&stuff);
    _tx_thread_sleep(42);
  }
}

static void consumer_main(uint32_t input) {
  for (;;) {
    tx_semaphore_get(&stuff, TX_WAIT_FOREVER);
    _tx_thread_sleep(7);
  }
}

void tx_application_define(void *first_unused_memory) {
  tx_byte_pool_create(&byte_pool, "Byte Pool", byte_pool_buffer,
                      sizeof(byte_pool_buffer));

  uint8_t *stack_start = NULL;
  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&blink, "Blinky", blink_main, 0, stack_start, 512, 1, 1,
                   TX_NO_TIME_SLICE, TX_AUTO_START);

  tx_semaphore_create(&stuff, "Stuff", 0);

  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&producer, "Producer", producer_main, 0, stack_start, 512, 1,
                   1, TX_NO_TIME_SLICE, TX_AUTO_START);

  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&consumer, "Consumer", consumer_main, 0, stack_start, 512, 1,
                   1, TX_NO_TIME_SLICE, TX_AUTO_START);
}
