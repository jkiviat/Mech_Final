#include "MotorPWM.h"

static volatile uint16_t pwm_run_period;

/**
 * Function Initialize_Motor_PWM initializes the motor PWM on Timer 1 for PWM based voltage control of the motors.
 * The Motor PWM system shall initialize in the disabled state for safety reasons. You should specifically enable
 * Motor PWM outputs only as necessary.
 * @param [uint16_t] MAX_PWM is the maximum PWM value to use. This controls the PWM frequency.
 */
// NOTES: ComnA1 1:0 control 
void Initialize_MotorPWM( uint16_t MAX_PWM ){
    MotorPWM_Set_Max(MAX_PWM);
    // Set phase and frequency PWM mode w/ ICR1 as TOP (mode 8 / 0b1000)
    // Also, set PWM to operate in non-inverted mode (clear on match, set at top)
    // Also, set clock source to no prescaler
    TCCR1A |= 0b10100000;
    TCCR1B |= 0b00010001;
    // Start in disabled state (0)
    OCR1A = 0;
    OCR1B = 0;
}

/**
 * Function MotorPWM_Enable enables or disables the motor PWM outputs.
 * @param [bool] enable (true set enable, false set disable)
 */
void MotorPWM_Enable( bool enable ){
    if(enable){
        // Set pins as outputs
        DDRB |= (1 << DDB6) | (1 << DDB5) | (1 << DDB2) | (1 << DDB1);
    } else {
        // Set pins as inputs (disable)
        DDRB &= ~((1 << DDB6) | (1 << DDB5) | (1 << DDB2) | (1 << DDB1));
    }
}

/**
 * Function MotorPWM_Is_Enabled returns if the motor PWM is enabled for output.
 * @param [bool] true if enabled, false if disabled
 */
bool MotorPWM_Is_Enabled(){
    return (DDRB >> DDB1) && (DDRB >> DDB2) && (DDRB >> DDB5) && (DDRB >> DDB6);
}

/**
 * Function MotorPWM_Set_Left sets the PWM duty cycle for the left motor.
 * @return [int32_t] The count number.
 */
void MotorPWM_Set_Left( int16_t pwm ){
    OCR1B = abs(pwm);
    if (pwm < 0){
        // Set PB2 to 1 for backwards
        PORTB |= (1 << PB2);
    } else {
        // Set PB2 to 0 for forwards
        PORTB &= ~(1 << PB2);
    }
}

/**
 * Function MototPWM_Set_Right sets the PWM duty cycle for the right motor.
 * @return [int32_t] The count number.
 */
void MotorPWM_Set_Right( int16_t pwm ){
    OCR1A = abs(pwm);
    if (pwm < 0){
        // Set PB1 to 1 for backwards
        PORTB |= (1 << PB1);
    } else {
        // Set PB1 to 0 for forwards
        PORTB &= ~(1 << PB1);
    }
}

/**
 * Function MotorPWM_Get_Left returns the current PWM duty cycle for the left motor. If disabled it returns what the
 * PWM duty cycle would be.
 * @return [int16_t] duty-cycle for the left motor's pwm
 */
int16_t MotorPWM_Get_Left(){
    bool is_rev = false;
    if((PORTB & (1 << PB2)) > 0){
        is_rev = true;
    }
    return (is_rev ? -1 : 1) * (int16_t) OCR1B;
}

/**
 * Function MotorPWM_Get_Right returns the current PWM duty cycle for the right motor. If disabled it returns what the
 * PWM duty cycle would be.
 * @return [int16_t] duty-cycle for the right motor's pwm
 */
int16_t MotorPWM_Get_Right(){
    bool is_rev = false;
    if((PORTB & (1 << PB1)) > 0){
        is_rev = true;
    }
    return (is_rev ? -1 : 1) * (int16_t) OCR1A;
}

/**
 * Function MotorPWM_Get_Max() returns the PWM count that corresponds to 100 percent duty cycle (all on), this is the
 * same as the value written into ICR1 as (TOP).
 */
uint16_t MotorPWM_Get_Max(){
    return ((uint16_t) ICR1H << 8) + ((uint16_t) ICR1L);
}

/**
 * Function MotorPWM_Set_Max sets the maximum pwm count. This function sets the timer counts to zero because
 * the ICR1 can cause undesired behaviors if change dynamically below the current counts.  See page 128 of the
 * atmega32U4 datasheat.
 */
void MotorPWM_Set_Max( uint16_t MAX_PWM ){
    // Lower half of MAX_PWM in IRC1L
    ICR1 = MAX_PWM;
}