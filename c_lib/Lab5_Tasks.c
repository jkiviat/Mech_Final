#include "Lab5_Tasks.h"

void Update_Controllers( float _unused ){

    float left_cont_val = Controller_Update(&p_cont_left, (float) Encoder_Counts_Left(), p_cont_left.update_period);
    float right_cont_val = Controller_Update(&p_cont_right, (float) Encoder_Counts_Right(), p_cont_right.update_period);

    MotorPWM_Set_Left(left_cont_val);
    MotorPWM_Set_Right(right_cont_val);
}
