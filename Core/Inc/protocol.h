//
// Created by bendi on 2026. 10. 10..
//

#ifndef BLP_GAMEPAD_1_PROTOCOL_H
#define BLP_GAMEPAD_1_PROTOCOL_H

#include <stdint.h>

typedef enum: uint8_t {
    KE_UP = 0,
    KE_DOWN,
    KE_CHANGE,
    MISSING
  } key_event_type_t;

typedef enum: uint8_t {
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
                uint8_t intensity;
            } key_event;

            struct {
                uint8_t version;
                uint8_t num_buttons;
                uint8_t flags;
            } info;

            uint8_t raw_data[3];
        };

        int8_t crc;
    };
    uint8_t raw[6];
} outbound_packet_t;

#pragma pack(pop)

static int8_t calculate_packet_checksum(outbound_packet_t pck) {
    return ((int8_t)0x7f) - pck.id - pck.raw_data[0] - pck.raw_data[1] - pck.raw_data[2];
}

#endif //BLP_GAMEPAD_1_PROTOCOL_H