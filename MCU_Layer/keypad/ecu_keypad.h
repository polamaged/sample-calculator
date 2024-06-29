/* 
 * File:   ecu_keypad.h
 * Author: polam
 *
 * Created on June 29, 2024, 4:17 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
// section : includes
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


// macro function
#define KEYPAD_ROWS    4
#define KEYPAD_COLOUMNS 4


//data type declaration 
typedef struct 
{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLOUMNS];

}keypad_t;

// software interface declaration
Std_ReturnType keypad_initialize(const keypad_t *keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *keypad_obj,uint8 *value);

#endif	/* ECU_KEYPAD_H */

