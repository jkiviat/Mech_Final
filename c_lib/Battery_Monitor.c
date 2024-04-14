#include "Battery_Monitor.h"

static const float BITS_TO_BATTERY_VOLTS = 0.0048f;

/*
static Filter_Data_t battery_voltage_filter;
static float vfilter_num[5] = {0.8485, -3.3939, 5.0909, -3.3939, 0.8485};
static float vfilter_den[5] = {1.0, -3.6717, 5.0680, -3.1160, 0.7199};
*/

// Battery voltage on pin ADC6
// Complete 10-bit ADC conversion found ADC9:0 ADCH (9:2) and ADCL (1:0) registers

/**
 * Function Initialize_Battery_Monitor initializes the Battery Monitor to record the current battery voltages.
 */
void Initialize_Battery_Monitor()
{
    // *** MEGN540 LAB3 YOUR CODE HERE ***
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN); // Enable ADC, set prescaler to 128
    //Filter_Init(&battery_voltage_filter, vfilter_num, vfilter_den, 4);
}

/**
 * Function Battery_Voltage initiates the A/D measurement and returns the result for the battery voltage.
 */
float Battery_Voltage()
{
    // A Union to assist with reading the LSB and MSB in the  16 bit register
    union {
        struct {
            uint8_t LSB;
            uint8_t MSB;
        } split;
        uint16_t value;
    } data = { .value = 0 };

    // *** MEGN540 LAB3 YOUR CODE HERE ***
    ADCSRA |= (1 << ADSC); // Start ADC convserion
    ADMUX = 0b11000110;
     // Switch ADMUX to ADC6 and make result left adjusted
    // Wait for conversion to finish
    while(bit_is_set(ADCSRA,ADSC)){;}
    // Read upper and lower registers
    data.split.LSB = ADCL;
    data.split.MSB = ADCH & 0b00000011;
    // Add MSB and LSB together
    data.value = (data.split.MSB << 8) + data.split.LSB;
    // Return
    return data.value * BITS_TO_BATTERY_VOLTS;
}

/*
void Read_Battery_Voltage(float _unused){
    // Read raw voltage into filter
    Filter_Value(&battery_voltage_filter, Battery_Voltage());
}
*/

float Filtered_Battery_Voltage(){
    // Return most recent filter value
    //return Filter_Last_Output(&battery_voltage_filter);
    return Battery_Voltage();
}