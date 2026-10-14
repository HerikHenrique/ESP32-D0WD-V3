#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"

static const char *TAG = "MAIN_BT";

void iniciar_bluetooth_classic(void) {
    ESP_LOGI(TAG, "Inicializando controlador Bluetooth...");
    
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    
    // 1. CORREÇÃO: Usando a constante atualizada do ESP-IDF v6.x
  // Altere de ESP_BT_MODE_CLASSIC_BT para ESP_BT_MODE_BTDM
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BTDM)); 

    
    ESP_LOGI(TAG, "Inicializando a Stack Bluedroid...");
    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());
    
    // 2. CORREÇÃO: Usando a nova API de GAP para definir o nome
    ESP_ERROR_CHECK(esp_bt_gap_set_device_name("Meu_ESP32_Classic"));
    
    // 3. CORREÇÃO: Ajustado para a assinatura do ESP-IDF v6.1 (dois argumentos: conexao e descoberta)
    ESP_ERROR_CHECK(esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE));
    
    ESP_LOGI(TAG, "Bluetooth ativado! Procure por 'Meu_ESP32_Classic' no seu celular.");
}

void app_main(void)
{
    // Inicializa a memória NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "Memória NVS inicializada.");

    // Chama a inicialização do Bluetooth
    iniciar_bluetooth_classic();
}

