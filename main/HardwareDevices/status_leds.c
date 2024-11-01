#include <esp_timer.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

#include "status_leds.h"

static uint8_t s_led_state = 0;
static led_strip_handle_t led_strip;

static void configure_status_leds(void)
{
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = CONFIG_STATUS_LEDS_GPIO,
        .max_leds = 2, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}

static void blink_led(void)
{

    s_led_state ^= 1;

    /* If the addressable LED is enabled */
    if (s_led_state)
    {
        /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
        led_strip_set_pixel(led_strip, 0, 0, 0, 16);
        led_strip_set_pixel(led_strip, 1, 0, 0, 0);
        /* Refresh the strip to send data */
        led_strip_refresh(led_strip);
    }
    else
    {
        led_strip_set_pixel(led_strip, 0, 0, 0, 0);
        led_strip_set_pixel(led_strip, 1, 0, 16, 0);
        led_strip_refresh(led_strip);
    }
}

void status_leds_task(void *arg)
{
    configure_status_leds();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        blink_led();
    }
}