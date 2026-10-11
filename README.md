# 1st gamepad for the BMEVIMIAC19 homework assignment

# MCU
Cheapest usable STM32 from HESTORE an STM32F030F4P6

# Serial protocol
Bidirectional at 9600 baud. Every message is 8 bytes. First byte is command, MSB of first byte is set in case of host->gamepad message. 
Then 6 bytes variable data. Last byte is checksum, which is the first 7 bytes XORd.

| CMD  | Name       | Data                                                                                                                                     |
|------|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| 0x01 | Key change | First byte is change type(DOWN = 0, UP, VALUE, MISSING), then 2 bytes button id, 2 bytes press intensity(0xFFFF for simple push buttons) |
| 0x02 | Info       | Gamepad version(1 byte), Num buttons(2 bytes), Flags(3 bytes)                                                                            |
| 0x03 | Pong       | 0xAA 0xBB 0xCC 0xDD 0xEE 0xFF                                                                                                            |
| 0x81 | Ping       | 0xFF 0xEE 0xDD 0xCC 0xBB 0xAA                                                                                                            |
| 0x82 | Identify   | I'm out of ideas, anything. Gamepad responds with 0x02.                                                                                  |
| 0x83 | Reset keys | Assume all keys are UP, send 0x01 for every key that isn't.                                                                              |

# Key table
| Hex  | Name    |
|------|---------|
| 0x00 | UNKNOWN |
| 0x01 | UP      |
| 0x02 | DOWN    |
| 0x03 | LEFT    |
| 0x04 | RIGHT   |
| 0x05 | B       |
| 0x06 | A       |
