/* 
 * File:   hal_gpio.h
 * Author: polam
 *
 * Created on June 29, 2024, 2:59 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
// section : includes
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/config.h"

// macro declaration
#define BIT_MASK (uint8)1
#define PORT_PIN_MAX_NUMBRE 8
#define PORT_MAX_NUMBER 5
#define PORTC_MASK  0xFF


// macro function
#define HWERG8(_x)(*((volatile uint8 *)(_x)))
#define SET_BIT(REG,BIT_POSN)    (REG |=(BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)  (REG &=~(BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN) (REG ^=(BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)   ((REG>>BIT_POSN)&BIT_MASK) 
//data type declaration 
typedef enum{
    GPIO_LOW,
    GPIO_HIGH
}Logic_t;
typedef enum{
    GPIO_OUTPUT=0,
    GPIO_INPUT
}direction_t;
typedef enum{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;
typedef enum{
    PORTA_INDEX =0,
    PORTB_INDEX ,
    PORTC_INDEX ,
    PORTD_INDEX ,
    PORTE_INDEX 
}port_index_t;

typedef struct{
    uint8 port : 3;      //@ref port_index_t
    uint8 pin : 3;       //@ref pin_index_t
    uint8 direction : 1; //@ref direction_t
    uint8 logic : 1;     //@ref Logic_t
}pin_config_t;
// function declaration 
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t*_pin_config);
Std_ReturnType gpio_pin_write_logic(const pin_config_t*_pin_config,Logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t*_pin_config, Logic_t *logic);
Std_ReturnType gpio_pin_intialize(const pin_config_t*_pin_config);


#endif	/* HAL_GPIO_H */

