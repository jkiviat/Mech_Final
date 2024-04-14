#include "Lab2_Tasks.h"

void Send_Loop_Time( float _time_since_last )
{
    char cmd;
    if (task_time_loop.run_period > 0) {
        cmd = 'T';
    } else {
        cmd = 't';
    }
    struct __attribute__(( __packed__ )) {
        unsigned short c1;
        float v2;
    } data;
    data.c1 = 0x01;
    data.v2 = loop_time_get(Timing_Get_Micro());
    USB_Send_Msg( "chf", cmd, &data, sizeof(data));
}

void Send_Time_Now( float _time_since_last )
{
    float time_now = Timing_Get_Time_Sec();
    char cmd;
    if (task_time_loop.run_period > 0) {
        cmd = 'T';
    } else {
        cmd = 't';
    }
    struct __attribute((__packed__)) {
        unsigned short c1;
        float v2;
    } data;
    data.c1 = 0x00;
    data.v2 = time_now;
    USB_Send_Msg("chf", cmd, &data, sizeof(data));
}