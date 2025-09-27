#include <tx_api.h>

#include <hardware/gpio.h>
#include <pico/time.h>

uint power_led = PICO_DEFAULT_LED_PIN;

TX_BYTE_POOL byte_pool;

TX_THREAD blink;

TX_THREAD producer;
TX_THREAD consumer;
TX_SEMAPHORE stuff;

TX_THREAD summoner;
TX_THREAD summon;
TX_SEMAPHORE spirit;

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
    tx_thread_sleep(42);
  }
}

static void consumer_main(uint32_t input) {
  for (;;) {
    tx_semaphore_get(&stuff, TX_WAIT_FOREVER);
    tx_thread_sleep(7);
  }
}

static void summon_main(uint32_t input) {
  tx_semaphore_put(&spirit);
  tx_thread_sleep(17);
}

static void summoner_main(uint32_t input) {
  tx_semaphore_create(&spirit, "Spirit", 0);

  uint8_t *summon_stack = NULL;
  tx_byte_allocate(&byte_pool, (void **)&summon_stack, 512, TX_NO_WAIT);

  for (;;) {
    tx_thread_create(&summon, "Summon", summon_main, 0, summon_stack, 512, 6, 1,
                     TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_semaphore_get(&spirit, TX_WAIT_FOREVER);

    UINT state = TX_READY;
    while (state != TX_COMPLETED) {
      tx_thread_sleep(13);
      tx_thread_info_get(&summon, NULL, &state, NULL, NULL, NULL, NULL, NULL,
                         NULL);
    }

    tx_thread_delete(&summon);

    tx_thread_sleep(77);
  }
}

void tx_application_define(void *first_unused_memory) {
  tx_byte_pool_create(&byte_pool, "Byte Pool", byte_pool_buffer,
                      sizeof(byte_pool_buffer));

  uint8_t *stack_start = NULL;
  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&blink, "Blinky", blink_main, 0, stack_start, 512, 3, 1,
                   TX_NO_TIME_SLICE, TX_AUTO_START);

  tx_semaphore_create(&stuff, "Stuff", 0);

  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&producer, "Producer", producer_main, 0, stack_start, 512, 5,
                   1, TX_NO_TIME_SLICE, TX_AUTO_START);

  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&consumer, "Consumer", consumer_main, 0, stack_start, 512, 4,
                   1, TX_NO_TIME_SLICE, TX_AUTO_START);

  tx_byte_allocate(&byte_pool, (void **)&stack_start, 512, TX_NO_WAIT);
  tx_thread_create(&summoner, "Summoner", summoner_main, 0, stack_start, 512, 7,
                   1, TX_NO_TIME_SLICE, TX_AUTO_START);
}
