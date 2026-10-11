//
// Created by bendi on 2026. 10. 10..
//

#ifndef BLP_GAMEPAD_1_PROTOCOL_H
#define BLP_GAMEPAD_1_PROTOCOL_H

#include <stdint.h>

typedef enum {
    KE_UP = 0,
    KE_DOWN,
    KE_CHANGE,
    MISSING
  } key_event_type_t;

typedef enum: uint16_t {
    KEY_UNKNOWN = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_B,
    KEY_A
  } key_t;

//Align to 1 byte(no padding)
#pragma pack(push, 1)

typedef union {
    struct {
        uint8_t id;

        union {
            struct {
                key_event_type_t type;
                key_t key;
                uint16_t intensity;
            } key_event;

            struct {
                uint8_t version;
                uint16_t num_buttons;
                uint8_t flags[3];
            } info;

            uint8_t raw_data[6];
        };

        uint8_t crc;
    };
    uint8_t raw[8];
} outbound_packet_t;

#pragma pack(pop)

static uint8_t calculate_packet_checksum(outbound_packet_t pck) {
    return pck.id ^ pck.raw_data[0] ^ pck.raw_data[1] ^ pck.raw_data[2] ^ pck.raw_data[3] ^ pck.raw_data[4] ^ pck.raw_data[5];
}

#endif //BLP_GAMEPAD_1_PROTOCOL_H