/*
 * D.Bojilov 2024
 */

#include <stdio.h>
#include <inttypes.h>
#include <esp_err.h>
#include <esp_freertos_hooks.h>
#include <esp_log.h>
#include <esp_timer.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "status_leds.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %lu bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    // Това работи само при: Component config/Log output/Maximum log verbosity = Verbose
    //      CONFIG_LOG_MAXIMUM_LEVEL_VERBOSE=y
    // esp_log_level_set("*", ESP_LOG_INFO);
    // esp_log_level_set("xpt2046", ESP_LOG_DEBUG);
    // esp_log_level_set("main", ESP_LOG_VERBOSE);

// проба на потребител @mitko125 и проба на проблем #pragma region 
//направено в main
//направено в test 
//@mitko125 #pragma region 
    int a = 0;
    //TODO: #5 #pragma endregion
    // #3
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
        ESP_LOGE(TAG, "nvs_flash_init");
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "Start status_leds_task");
    xTaskCreate(status_leds_task, "status_leds_task", 2 * 4096, NULL, 5, NULL);

    while (1)
    {
        //vTaskDelay(10 / portTICK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(10));
        int c = fgetc(stdin);
        if (c > 0)
            printf("Echo \'%c\'\n", c);
    }

    vTaskDelete( NULL );
}
