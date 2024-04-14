/*
         MEGN540 Mechatronics Lab
    Copyright (C) Andrew Petruska, 2021.
       apetruska [at] mines [dot] edu
          www.mechanical.mines.edu
*/

/*
    Copyright (c) 2021 Andrew Petruska at Colorado School of Mines

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

// put your includes here for all modules you need to use

#include "Message_Handling.h"  // for translating USB messages to microcontroller tasks
#include "SerialIO.h"          // for USB communication
#include "Task_Management.h"   // for clean task management with functors
#include "Timing.h"            // for Time understanding
#include "Encoder.h"
#include "MotorPWM.h"
#include "Controller.h"

#include "Lab1_Tasks.h"
#include "Lab2_Tasks.h"
#include "Lab3_Tasks.h"
#include "Lab4_Tasks.h"

// put your task includes and/or function declarations here for future populaion


// put your global variables (only if absolutely required) here.
// Best to identify them as "static" to make them indentified as internal and start with a "_" to identify as internal.
// Try to initialize them if possible, so their values are never arbitrary.

// put your initialization function here


float left_cont_a[2] = {114.4, -113.8616};
float left_cont_b[2] = {1, -0.4608};
float left_cont_kp = 0.4;

float right_cont_a[2] = {114.4, -113.8616};
float right_cont_b[2] = {1, -0.4608};
float right_cont_kp = 0.4;

void Initialize_Modules( float _time_not_used_ )
{
    // Initialize (reinitialize) all global variables

    // reset USB input buffers
    USB_Flush_Input_Buffer();

    // Initialize all modules except USB (it can only be called once without messing things up)
    Initialize_Timing();
    Initialize_Encoders();
    Initialize_Battery_Monitor();
    Initialize_MotorPWM(1000);

    Initialize_Controller(&p_cont_left, left_cont_kp, left_cont_b, left_cont_a, 1, 0.001);
    Initialize_Controller(&p_cont_right, right_cont_kp, right_cont_b, right_cont_a, 1, 0.001);

    Initialize_Task( &task_restart, Initialize_Modules );
    
    Initialize_Task( &task_message_handling, Task_Message_Handling );

    Initialize_Task(&task_time_loop, Send_Loop_Time);

    Initialize_Task(&task_send_time, Send_Time_Now);

    Initialize_Task(&task_send_encoder_counts, Send_Encoder_Counts);

    Initialize_Task(&task_send_battery_voltage, Send_Battery_Voltage);

    Initialize_Task(&task_warn_battery_voltage, Send_Voltage_Warning);

    Initialize_Task( &task_message_handling_watchdog, Task_Message_Handling_Watchdog );

    Initialize_Task( &task_disable_pwm, Disable_Pwm );

    Initialize_Task( &task_send_sysid, Send_Sysid );

    Initialize_Task ( &task_update_controllers, Update_Controllers );

    Task_Activate( &task_message_handling_watchdog, 0.25);

    Task_Activate( &task_message_handling, 0);

    Task_Activate( &task_warn_battery_voltage, 5);

    Task_Activate ( &task_update_controllers, 0.001 ); 
}

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main( void )
{
    Initialize_USB();
    Initialize_Modules( 0.0 );

    for( ;; ) {  // yet another way to do while (true)
        loop_time_set();

        Task_USB_Upkeep();

        Task_Run_If_Ready( &task_send_time );
        Task_Run_If_Ready( &task_time_loop );

        Task_Run_If_Ready( &task_send_encoder_counts );
        Task_Run_If_Ready( &task_send_battery_voltage );
        Task_Run_If_Ready( &task_warn_battery_voltage );

        Task_Run_If_Ready( &task_disable_pwm );
        Task_Run_If_Ready( &task_send_sysid );

        Task_Run_If_Ready( &task_update_controllers );

        Task_Run_If_Ready( &task_restart );
        Task_Run_If_Ready( &task_message_handling );
        Task_Run_If_Ready( &task_message_handling_watchdog );
    }
}

// put your task function definitions here
