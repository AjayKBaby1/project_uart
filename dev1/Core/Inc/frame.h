#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define START_BYTE 0xAA

uint8_t Frame_Build(uint8_t return_proto,
                    uint8_t value,
                    uint8_t *frame_out);

uint8_t Frame_Parse(uint8_t *frame,
                    uint8_t *return_proto,
                    uint8_t *value);

#endif
