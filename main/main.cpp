//
// Created by Braden Nicholson on 6/13/22.
//


#include <esp_timer.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include "dmx.cpp"
#include "server.h"
#include "indicator.h"
#include "persistent.h"

int millis() {
    return (int)esp_timer_get_time() / 1000;
}

void loop(void *pc) {
    int lastTick = millis();
    while(true) {
        if(millis() - lastTick >= 1000) {
            lastTick = millis();
        }
    }
}

void restoreDefault() {
    auto persistent = Persistent("defaults");
    for (int i = 1; i <= 16; ++i) {
        uint8_t value = persistent.readU8("ch", i);
        DMX::Write(i, value);
    }
    persistent.close();
}


extern "C" void app_main(void) {

    DMX::Initialize(output);

    initIndicator();
    setIndicator(BLUE);

    // Load in the default values from Flash
    restoreDefault();

    setupServer();

    setIndicator(GREEN);


    TaskHandle_t xHandle = NULL;

    xTaskCreate(loop, "mainLoop", 4096, NULL, 0, &xHandle);
}
