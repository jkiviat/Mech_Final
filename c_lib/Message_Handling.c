/*
         MEGN540 Mechatronics Lab
    Copyright (C) Andrew Petruska, 2021.
       apetruska [at] mines [dot] edu
          www.mechanical.mines.edu
*/

/*
    Copyright (c) 2021 Andrew Petruska at Colorado School of Mines

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.

*/

#include "Message_Handling.h"

/**
 * Function _Message_Length returns the number of bytes associated with a command string per the
 * class documentation; This is only accessable from this file.
 * @param cmd
 * @return Size of expected string. Returns 0 if unrecognized.
 */
static uint8_t _Message_Length( char cmd );

/**
 * Function Task_Message_Handling processes USB messages as necessary and sets
 * status flags to control the flow of the program.
 */
void Task_Message_Handling( float _time_since_last )
{
    // *** MEGN540  ***
    // YOUR CODE HERE. I suggest you use your peak function and a switch interface
    // Either do the simple stuff strait up, set flags to have it done later.
    // If it just is a USB thing, do it here, if it requires other hardware, do it
    // in the main and set a flag to have it done here.

    // Check to see if their is data in waiting
    if( !USB_Msg_Length() )
        return;  // nothing to process...

    // Get Your command designator without removal so if their are not enough
    // bytes yet, the command persists
    char command = USB_Msg_Peek();

    bool command_processed = false;

    // process command
    switch( command ) {
        case '*':
            if( USB_Msg_Length() >= _Message_Length( '*' ) ) {
                // then process your multiplication...

                // remove the command from the usb recieved buffer using the
                // usb_msg_get() function
                USB_Msg_Get();  // removes the first character from the received buffer,
                                // we already know it was a * so no need to save it as a
                                // variable

                // Build a meaningful structure to put your data in. Here we want two
                // floats.
                struct __attribute__( ( __packed__ ) ) {
                    float v1;
                    float v2;
                } data;

                // Copy the bytes from the usb receive buffer into our structure so we
                // can use the information
                USB_Msg_Read_Into( &data, sizeof( data ) );

                // Call MEGN540_Lab_Task Function
                Multiply_And_Send( data.v1, data.v2 );

                // /* MEGN540 -- LAB 2 */ 
                command_processed = true;
            }
            break;
        case '/':
            if( USB_Msg_Length() >= _Message_Length( '/' ) ) {
                // then process your multiplication...

                // remove the command from the usb recieved buffer using the
                // usb_msg_get() function
                USB_Msg_Get();  // removes the first character from the received buffer,
                                // we already know it was a * so no need to save it as a
                                // variable

                // Build a meaningful structure to put your data in. Here we want two
                // floats.
                struct __attribute__( ( __packed__ ) ) {
                    float v1;
                    float v2;
                } data;

                // Copy the bytes from the usb receive buffer into our structure so we
                // can use the information
                USB_Msg_Read_Into( &data, sizeof( data ) );

                // Call MEGN540_Lab_Task Function
                Divide_And_Send( data.v1, data.v2 );

                // /* MEGN540 -- LAB 2 */ 
                command_processed = true;
            }
            break;
        case '+':
            if( USB_Msg_Length() >= _Message_Length( '+' ) ) {
                // then process your multiplication...

                // remove the command from the usb recieved buffer using the
                // usb_msg_get() function
                USB_Msg_Get();  // removes the first character from the received buffer,
                                // we already know it was a * so no need to save it as a
                                // variable

                // Build a meaningful structure to put your data in. Here we want two
                // floats.
                struct __attribute__( ( __packed__ ) ) {
                    float v1;
                    float v2;
                } data;

                // Copy the bytes from the usb receive buffer into our structure so we
                // can use the information
                USB_Msg_Read_Into( &data, sizeof( data ) );

                // Call MEGN540_Lab_Task Function
                Add_And_Send( data.v1, data.v2 );

                // /* MEGN540 -- LAB 2 */ 
                command_processed = true;
            }
            break;
        case '-':
            if( USB_Msg_Length() >= _Message_Length( '-' ) ) {
                // then process your multiplication...

                // remove the command from the usb recieved buffer using the
                // usb_msg_get() function
                USB_Msg_Get();  // removes the first character from the received buffer,
                                // we already know it was a * so no need to save it as a
                                // variable

                // Build a meaningful structure to put your data in. Here we want two
                // floats.
                struct __attribute__( ( __packed__ ) ) {
                    float v1;
                    float v2;
                } data;

                // Copy the bytes from the usb receive buffer into our structure so we
                // can use the information
                USB_Msg_Read_Into( &data, sizeof( data ) );

                // Call MEGN540_Lab_Task Function
                Subtract_And_Send( data.v1, data.v2 );

                // /* MEGN540 -- LAB 2 */ 
                command_processed = true;
            }
            break;
        case '~':
            if(USB_Msg_Length() >= _Message_Length('~')) {
                USB_Msg_Get();
                task_restart.is_active = true;
                command_processed = true;
            }
            break;
        case 't':
            if( USB_Msg_Length() >= _Message_Length( 't' )){
                USB_Msg_Get();
                uint8_t time_config = USB_Msg_Get();
                switch(time_config){
                    case '0':
                        Task_Activate(&task_send_time,-1);
                        break;
                    case '1':
                        Task_Activate(&task_time_loop,-1);
                        break;
                }
                command_processed = true;
            }
            break;
        case 'T':
            if( USB_Msg_Length() >= _Message_Length('T')){
                USB_Msg_Get();
                uint8_t time_config = USB_Msg_Get();
                float loop_time;
                USB_Msg_Read_Into(&loop_time, sizeof(loop_time));
                if (loop_time > 0) {
                    switch(time_config){
                        case '0':
                            Task_Activate(&task_send_time,loop_time*0.001);
                            break;
                        case '1':
                            Task_Activate(&task_time_loop, loop_time*0.001);
                            break;
                    }
                } else {
                    switch(time_config){
                        case '0':
                            Task_Cancel(&task_send_time);
                            break;
                        case '1':
                            Task_Cancel(&task_time_loop);
                            break;
                    }
                }
                command_processed = true;
            }   
            break;
        case 'e':
            if( USB_Msg_Length() >= _Message_Length( 'e' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                // Activate encoder counts
                Task_Activate(&task_send_encoder_counts,-1);
                command_processed = true;
            }
            break;
        case 'E':
            if( USB_Msg_Length() >= _Message_Length('E')){
                // Get rid of character in buffer
                USB_Msg_Get();
                // Read loop time
                float loop_time;
                USB_Msg_Read_Into(&loop_time, sizeof(loop_time));
                // Start loop or stop
                if (loop_time > 0) {
                    Task_Activate(&task_send_encoder_counts,loop_time*0.001);
                } else {
                    Task_Cancel(&task_send_encoder_counts);
                }
                command_processed = true;
            }   
            break;
        case 'b':
            if( USB_Msg_Length() >= _Message_Length( 'b' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                Task_Activate(&task_send_battery_voltage,-1);
                command_processed = true;
            }
            break;
        case 'B':
            if( USB_Msg_Length() >= _Message_Length('B')){
                // Get rid of character in buffer
                USB_Msg_Get();
                // Read loop time
                float loop_time;
                USB_Msg_Read_Into(&loop_time, sizeof(loop_time));
                // Start loop or stop
                if (loop_time > 0) {
                    Task_Activate(&task_send_battery_voltage,loop_time*0.001);
                } else {
                    Task_Cancel(&task_send_battery_voltage);
                }
                command_processed = true;
            }   
            break;
        case 'q':
            if( USB_Msg_Length() >= _Message_Length( 'q' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                Task_Activate(&task_send_sysid,-1);
                command_processed = true;
            }
            break;
        case 'Q':
            if( USB_Msg_Length() >= _Message_Length( 'Q' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                // Get loop time
                float loop_time;
                USB_Msg_Read_Into(&loop_time, sizeof(loop_time));
                // Start loop or stop
                if (loop_time > 0) {
                    Task_Activate(&task_send_sysid,loop_time*0.001);
                } else {
                    Task_Cancel(&task_send_sysid);
                }
                command_processed = true;
            }
            break;
        case 'p':
            if( USB_Msg_Length() >= _Message_Length( 'p' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                struct __attribute__( ( __packed__ ) ) {
                    int16_t v1;
                    int16_t v2;
                } data;
                // Copy the bytes from the usb receive buffer into our structure so we
                // can use the information
                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Check battery voltage, don't run if battery is too low or power off
                float battery_voltage = Battery_Voltage();
                // Low battery
                if( battery_voltage >= 2.0 && battery_voltage <= 4.0 ){
                    struct {char let[7]; float volts; } data = { .let = {'B','A','T',' ','L','O', 'W'}, .volts = battery_voltage };
                    USB_Send_Msg( "c7sf", '!',  &data, sizeof(data) );
                    // Just in case, disable motors
                    MotorPWM_Enable(false);
                }
                // Power off
                else if( battery_voltage < 2.0 ){
                    struct {char let[9]; } data = { .let = {'P','O','W','E','R', ' ', 'O', 'F', 'F'} };
                    USB_Send_Msg( "c9s", '!',  &data, sizeof(data) );
                    // Just in case, disable motors
                    MotorPWM_Enable(false);
                }
                // Good to go
                else {
                    // Set PWM values, enable PWM
                    MotorPWM_Set_Left(data.v1);
                    MotorPWM_Set_Right(data.v2);
                    MotorPWM_Enable(true);
                }
                command_processed = true;
            }
            break;
        case 'P':
            if( USB_Msg_Length() >= _Message_Length( 'P' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                struct __attribute__( ( __packed__ ) ) {
                    int16_t v1;
                    int16_t v2;
                    float v3;
                } data;
                // Read data from message
                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Check battery voltage, don't run if battery is too low or power off
                float battery_voltage = Battery_Voltage();
                // Low battery
                if( battery_voltage >= 2.0 && battery_voltage <= 4.0) {
                    struct {char let[7]; float volts; } data = { .let = {'B','A','T',' ','L','O', 'W'}, .volts = battery_voltage };
                    USB_Send_Msg( "c7sf", '!',  &data, sizeof(data) );
                    // Just in case, disable motors
                    MotorPWM_Enable(false);
                }
                // Power off
                else if( battery_voltage < 2.0 ){
                    struct {char let[9]; } data = { .let = {'P','O','W','E','R', ' ', 'O', 'F', 'F'} };
                    USB_Send_Msg( "c9s", '!',  &data, sizeof(data) );
                    // Just in case, disable motors
                    MotorPWM_Enable(false);
                }
                // Good to go
                else {
                    // Set PWM values, enable PWM
                    MotorPWM_Set_Left(data.v1);
                    MotorPWM_Set_Right(data.v2);
                    MotorPWM_Enable(true);
                    // Disable after specified time period
                    Task_Activate( &task_disable_pwm, data.v3 * 0.001 );
                }
                command_processed = true;
            }
            break;
        case 's':
            if( USB_Msg_Length() >= _Message_Length( 's' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                MotorPWM_Enable(false);
                command_processed = true;
            }
            break;
        case 'S':
            if( USB_Msg_Length() >= _Message_Length( 'S' )){
                // Get rid of character in buffer
                USB_Msg_Get();
                MotorPWM_Enable(false);
                command_processed = true;
            }
            break;
        case 'd':
            if( USB_Msg_Length() >= _Message_Length( 'd' )){
                // Get rid of character in buffer
                USB_Msg_Get();

                struct __attribute__( ( __packed__ ) ) {
                    float linear_pos;
                    float angular_pos;
                } data;

                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Calculate desire distances. conver to encoder count
                float left_distance_desired = (data.linear_pos - ((0.098 / 2) * data.angular_pos))* (1.0 / 0.000134684) + Encoder_Counts_Left();
                float right_distance_desired= (data.linear_pos + ((0.098 / 2) * data.angular_pos))* (1.0 / 0.000134684) + Encoder_Counts_Right();
                // set target positions
                Controller_Set_Target_Position(&p_cont_left, left_distance_desired);
                Controller_Set_Target_Position(&p_cont_right, right_distance_desired);

                MotorPWM_Enable(true);
                command_processed = true;
            }
            break;
        case 'D':
            if( USB_Msg_Length() >= _Message_Length( 'D' )){
                // Get rid of character in buffer
                USB_Msg_Get();

                struct __attribute__( ( __packed__ ) ) {
                    float linear_pos;
                    float angular_pos;
                    float time;
                } data;

                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Calculate desire distances. conver to encoder count          
                float left_distance_desired = (data.linear_pos - ((0.098 / 2) * data.angular_pos))* (1.0 / 0.000134684) + Encoder_Counts_Left();
                float right_distance_desired= (data.linear_pos + ((0.098 / 2) * data.angular_pos))* (1.0 / 0.000134684) + Encoder_Counts_Right();
                // set target positions
                Controller_Set_Target_Position(&p_cont_left, left_distance_desired);
                Controller_Set_Target_Position(&p_cont_right, right_distance_desired);

                // enable motors
                MotorPWM_Enable(true);
                // disable task after time
                Task_Activate( &task_disable_pwm, data.time);
                command_processed = true;
            }
            break;
        case 'v':
            if( USB_Msg_Length() >= _Message_Length( 'v' )){
                // Get rid of character in buffer
                USB_Msg_Get();

                struct __attribute__( ( __packed__ ) ) {
                    float linear_vel;
                    float angular_vel;
                } data;
                // Read data from message
                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Calculate desire velocity. conver to encoder count per sec
                float left_velocity_desired = (data.linear_vel - ((0.098 / 2) * data.angular_vel))* (1.0 / 0.000134684);
                float right_velocity_desired= (data.linear_vel + ((0.098 / 2) * data.angular_vel))* (1.0 / 0.000134684);
                // set target velocity
                Controller_Set_Target_Velocity(&p_cont_left, left_velocity_desired );
                Controller_Set_Target_Velocity(&p_cont_right, right_velocity_desired );
                // enable motors
                MotorPWM_Enable(true);
                command_processed = true;
            }
            break;
        case 'V':
            if( USB_Msg_Length() >= _Message_Length( 'V' )){
                // Get rid of character in buffer
                USB_Msg_Get();

                struct __attribute__( ( __packed__ ) ) {
                    float linear_vel;
                    float angular_vel;
                    float time;
                } data;
                // Read data from message
                USB_Msg_Read_Into( &data, sizeof( data ) );
                // Calculate desire velocity. conver to encoder count per sec
                float left_velocity_desired = (data.linear_vel - ((0.098 / 2) * data.angular_vel))* (1.0 / 0.000134684);
                float right_velocity_desired= (data.linear_vel + ((0.098 / 2) * data.angular_vel))* (1.0 / 0.000134684);
                // set target velocity
                Controller_Set_Target_Velocity(&p_cont_left, left_velocity_desired );
                Controller_Set_Target_Velocity(&p_cont_right, right_velocity_desired );

                // enable motors
                MotorPWM_Enable(true);
                // disable task after time
                Task_Activate( &task_disable_pwm, data.time);
                command_processed = true;
            }
            break;
        default:
            // What to do if you dont recognize the command character
            USB_Msg_Get();
            command_processed = true;
            break;
    }

    //********* MEGN540 -- LAB 2 ************//
    if( command_processed ) {
         // RESET the WATCHDOG TIMER
         Task_Activate( &task_message_handling_watchdog, 0.25 );
    }
}

/**
 * @brief Function Task_Message_Handling_Watchdog clears the USB recieve (deleting all messages) to flush the buffer if a complete message is not recieved
 * whithin an appropriate amount of time (say 250ms)
 *
 * @param _unused_
 */
void Task_Message_Handling_Watchdog( float _unused_ )
{
    USB_Flush_Input_Buffer();
}

/**
 * Function _Message_Length returns the number of bytes associated with a
 * command string per the class documentation;
 * @param cmd
 * @return Size of expected string. Returns 0 if unreconized.
 */
static uint8_t _Message_Length( char cmd )
{
    switch( cmd ) {
        case '~': return 1; break;
        case '*': return 9; break;
        case '/': return 9; break;
        case '+': return 9; break;
        case '-': return 9; break;
        case 't': return 2; break;
        case 'T': return 6; break;
        case 'e': return 1; break;
        case 'E': return 5; break;
        case 'b': return 1; break;
        case 'B': return 5; break;
        case 'p': return 5; break;
        case 'P': return 9; break;
        case 's': return 1; break;
        case 'S': return 1; break;
        case 'q': return 1; break;
        case 'Q': return 5; break;
        case 'd': return 9; break;
        case 'D': return 13; break;
        case 'v': return 9; break;
        case 'V': return 13; break;
        default: return 0; break;
    }
}
