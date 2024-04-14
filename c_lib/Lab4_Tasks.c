#include "Lab4_Tasks.h"

void Disable_Pwm(float _unused){
    MotorPWM_Enable(false);
    Task_Cancel(&task_disable_pwm);
}

void Send_Sysid(float _unused){
    char cmd;
    // Check if in loop or one-off
    if (task_send_sysid.run_period > 0) {
        cmd = 'Q';
    } else {
        cmd = 'q';
    }
    // Read all necessary data
    struct __attribute__((__packed__)){
        float time;
        int16_t pwm_l;
        int16_t pwm_r;
        int16_t enc_l;
        int16_t enc_r;
    } data;
    data.time = Timing_Get_Time_Sec();
    data.enc_l = Encoder_Counts_Left();
    data.enc_r = Encoder_Counts_Right();
    data.pwm_l = MotorPWM_Get_Left();
    data.pwm_r = MotorPWM_Get_Right();
    // Send message
    USB_Send_Msg("cf4h", cmd, &data, sizeof(data));
}