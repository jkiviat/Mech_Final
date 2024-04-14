#include "Encoder.h"

/**
 * Internal counters for the Interrupts to increment or decrement as necessary.
 */
static volatile bool _last_right_A = 0;  // Static limits it's use to this file
static volatile bool _last_right_B = 0;  // Static limits it's use to this file

static volatile bool _last_left_A   = 0;  // Static limits it's use to this file
static volatile bool _last_left_B   = 0;  // Static limits it's use to this file
static volatile bool _last_left_XOR = 0;  // Necessary to check if PB4 triggered the ISR or not

static volatile int32_t _left_counts  = 0;  // Static limits it's use to this file
static volatile int32_t _right_counts = 0;  // Static limits it's use to this file

/** Helper Funcions for Accessing Bit Information */
// *** MEGN540 Lab 3 TODO ***
// Hint, use avr's bit_is_set function to help
static inline bool Right_XOR()
{
    return bit_is_set(PINE,PE6);
}  


static inline bool Right_B()
{
    return bit_is_set(PINF,PF0);
}  

static inline bool Right_A()
{
    return Right_XOR()^Right_B();
}  

static inline bool Left_XOR()
{
    return bit_is_set(PINB,PB4);
}  

static inline bool Left_B()
{
    return bit_is_set(PINE,PE2);
}  

static inline bool Left_A()
{
    return Left_XOR() ^ Left_B();
}  

/**
 * Function Encoders_Init initializes the encoders, sets up the pin change interrupts, and zeros the initial encoder
 * counts.
 */
void Initialize_Encoders()
{
    // *** MEGN540 Lab3 ***
    // YOUR CODE HERE
    // Set pins as inputs:
    DDRE &= ~(1 << PE2);
    DDRB &= ~(1 << PB4);
    DDRE &= ~(1 << PE6);
    DDRF &= ~(1 << PF0);


    // Left encoder uses PB4 and PE2 pins as digital inputs. External interrupt PCINT4 is necessary to detect
    // the change in XOR flag. You'll need to see Section 11.1.5 - 11.1.7 for setup and use.
    // Note that the PCINT interrupt is trigered by any PCINT pin. In the ISR you should check to make sure
    // the interrupt triggered is the one you intend on processing.
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT4);


    // Right encoder uses PE6 adn PF0 as digital inputs. External interrupt INT6 is necessary to detect
    // the changes in XOR flag. You'll need to see Sections 11.1.2-11.1.4 for setup and use.
    // You'll use the INT6_vect ISR flag.
    EICRB |= (1 << ISC60);
    EIMSK |= (1 << INT6);



    // Initialize static file variables. These probably need to be updated.
    _last_right_A = 0;  // MEGN540 Lab 3 TODO
    _last_right_B = 0;  // MEGN540 Lab 3 TODO

    _last_left_A   = 0;  // MEGN540 Lab 3 TODO
    _last_left_B   = 0;  // MEGN540 Lab 3 TODO
    _last_left_XOR = 0;  // MEGN540 Lab 3 TODO

    _left_counts  = 0;  // MEGN540 Lab 3 TODO
    _right_counts = 0;  // MEGN540 Lab 3 TODO

    sei();
}

/**
 * Function Encoder_Counts_Left returns the number of counts from the left encoder.
 * @return [int32_t] The count number.
 */
int32_t Encoder_Counts_Left()
{    
    // stop interrupts, copy the value, and re-enable interrupts to prevent this from corrupting your read/write.
    int32_t counts;
    cli();
    counts = _left_counts;
    sei();
    return counts;

}

/**
 * Function Encoder_Counts_Right returns the number of counts from the right encoder.
 * @return [int32_t] The count number.
 */
int32_t Encoder_Counts_Right()
{
    // stop interrupts, copy the value, and re-enable interrupts to prevent this from corrupting your read/write.
    int32_t counts;
    cli();
    counts = _right_counts;
    sei();
    return counts;

}

/**
 * Function Encoder_Rad_Left returns the number of radians for the left encoder.
 * @return [float] Encoder angle in radians
 */
float Encoder_Rad_Left()
{

    return (2 * 3.14159265 * Encoder_Counts_Left()) / 909.7; //2*pi --> 12 encoder count // to get encoder count in radian: (2*pi*Encoder_Count)/counts_per_rotation 
}

/**
 * Function Encoder_Rad_Right returns the number of radians for the left encoder.
 * @return [float] Encoder angle in radians
 */
float Encoder_Rad_Right()
{
    
    return (2 * 3.14159265 * Encoder_Counts_Right()) / 909.7; //2*pi --> 12 encoder count // to get encoder count in radian: (2*pi*Encoder_Count)/counts_per_rotation 
}

/**
 * Interrupt Service Routine for the left Encoder. Note: May need to check that it is actually PCINT4 that triggered, as
 * the Pin Change Interrupts can trigger for multiple pins.
 * @return
 */
ISR(PCINT0_vect)
{
    bool left_XOR = Left_XOR();

    // If PCINT4 triggered this interrupt...
    if(left_XOR != _last_left_XOR){
        // Get A and B levels
        bool left_A = Left_A();
        bool left_B = Left_B();

        // Increment or decrement left counts
        _left_counts += (left_A ^ _last_left_B) - (_last_left_A ^ left_B);

        // Save pin values
        _last_left_A = left_A;
        _last_left_B = left_B;
    }
    // Save pin value
    _last_left_XOR = left_XOR;
}

/**
 * Interrupt Service Routine for the right Encoder.
 * @return
 */
ISR(INT6_vect)
{
    // Get A and B levels
    bool right_A = Right_A();
    bool right_B = Right_B();

    // Increment or decrement right counts
    _right_counts += (right_A ^ _last_right_B) - (_last_right_A ^ right_B);

    // Save pin values
    _last_right_A = right_A;
    _last_right_B = right_B;

}