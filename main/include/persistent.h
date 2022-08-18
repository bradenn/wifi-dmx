//
// Created by Braden Nicholson on 8/18/22.
//

#ifndef RS485_DMX_PERSISTANT_H
#define RS485_DMX_PERSISTANT_H

#include <cstdint>
#include <esp_err.h>
#include <nvs_flash.h>
#include "string"

using std::string;
class Persistent {
public:

    explicit Persistent(const string& selector);

    ~Persistent();

    nvs_handle_t handle{};
    uint8_t readU8(const string& selector, int value) const;
    uint8_t writeU8(const string& selector, int key, uint8_t value) const;
    void close();
private:

};


#endif //RS485_DMX_PERSISTANT_H
