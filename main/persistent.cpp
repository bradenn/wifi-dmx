//
// Created by Braden Nicholson on 8/18/22.
//


#include <esp_log.h>
#include "persistent.h"
#include "dmx.h"

const char* TAG = "PERSISTENT";

Persistent::Persistent(const string& section) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    err = nvs_open(section.c_str(), NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {

    }
}

uint8_t Persistent::readU8(const string& selector, int value) const {
    char location[12];
    uint8_t output = 0;
    sprintf(location, "%s%d", selector.c_str(), value);

    auto err = nvs_get_u8(handle, location, &output);
    switch (err) {
        case ESP_OK:
            ESP_LOGI(TAG, "read: %s -> %d", location, output);
            return output;
        case ESP_ERR_NVS_NOT_FOUND:
            err = nvs_set_u8(handle, location, 0);
            if (err != ESP_OK) {
                ESP_LOGI(TAG, "NVS Write failed");
            }
            err = nvs_commit(handle);
            if (err != ESP_OK) {
                ESP_LOGI(TAG, "NVS Commit failed");
            }
            return 0;
        default :
            ESP_LOGI(TAG, "NVS Read failed");
    }

    return 0;
}

uint8_t Persistent::writeU8(const string &selector, int key, uint8_t value) const {
    char location[12];
    sprintf(location, "%s%d", selector.c_str(), key);
    auto err = nvs_set_u8(handle, location, value);
    if (err != ESP_OK) {
        ESP_LOGI(TAG, "NVS Write failed");
    }
    err = nvs_commit(handle);
    if (err != ESP_OK) {
        ESP_LOGI(TAG, "NVS Commit failed");
    }
    return value;
}

void Persistent::close() {
    nvs_close(handle);
}

Persistent::~Persistent() {

}


