#include <stdio.h>
#include "nvs_flah.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    // Inicializa a memória NVS (Obrigatório para Bluetooth)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // Se a memória estiver cheia ou corrompida, limpa e tenta inicializar novamente
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Memória NVS inicializada com sucesso!");
    ESP_LOGI(TAG, "Pronto para começar a configurar o Bluetooth.");
}
