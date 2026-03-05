#include "frame.h"

uint8_t Frame_Build(uint8_t return_proto,
                    uint8_t value,
                    uint8_t *frame_out)
{
    uint8_t checksum = return_proto + value;

    frame_out[0] = START_BYTE;
    frame_out[1] = 2;
    frame_out[2] = return_proto;
    frame_out[3] = value;
    frame_out[4] = checksum;

    return 5;
}

uint8_t Frame_Parse(uint8_t *frame,
                    uint8_t *return_proto,
                    uint8_t *value)
{
    if(frame[0] != START_BYTE)
        return 0;

    if(frame[1] != 2)
        return 0;

    uint8_t checksum = frame[2] + frame[3];

    if(checksum != frame[4])
        return 0;

    *return_proto = frame[2];
    *value        = frame[3];

    return 1;
}
