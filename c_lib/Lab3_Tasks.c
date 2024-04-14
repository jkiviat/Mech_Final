#include "Lab3_Tasks.h"

void Send_Encoder_Counts(float _time_since_last) {
    char cmd;
    // Check if in loop or one-off
    if (task_send_encoder_counts.run_period > 0) {
        cmd = 'E';
    } else {
        cmd = 'e';
    }
    // Read both encoder counts
    struct __attribute__((__packed__)){
        uint16_t c1;
        uint16_t c2;
    } data;
    data.c1 = Encoder_Counts_Left();
    data.c2 = Encoder_Counts_Right();
    // Send message
    USB_Send_Msg("chh", cmd, &data, sizeof(data));
}

void Send_Battery_Voltage(float _time_since_last) {
    char cmd;
    // Check if in loop or one-off
    if (task_send_battery_voltage.run_period > 0) {
        cmd = 'B';
    } else {
        cmd = 'b';
    }
    // Read filtered battery voltage
    float data = Filtered_Battery_Voltage();
    // Send message
    USB_Send_Msg ("cf", cmd, &data, sizeof(data));
}

void Send_Voltage_Warning(float _time_since_last) {
    float batt_voltage = Filtered_Battery_Voltage();
    // Send warning if battery voltage greater than 1.2, less than 3.6
    if(batt_voltage <= 4.0 && batt_voltage >= 3.0){
        // Create msg struct
        struct __attribute__((__packed__)) {char let[7]; float volt;} msg =
        {
            .let = {'B','A','T',' ','L','O','W'},
            .volt = batt_voltage
        };
        // Send Warning to Serial that batteries need to be charged
        USB_Send_Msg("c7sf",'!', &msg, sizeof(msg));
    }
}