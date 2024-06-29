#include "hal_gpio.h"


volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};


Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config)
{ 
    Std_ReturnType ret =E_OK;
    if(NULL == _pin_config || _pin_config->pin >PORT_PIN_MAX_NUMBRE-1)
        ret=E_NOT_OK;
    else
    {
        switch(_pin_config->direction)
        {
        case GPIO_OUTPUT:
            CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        case GPIO_INPUT:
            SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        default :ret = E_NOT_OK ;
                        
        }
    }
    return ret;
}

Std_ReturnType gpio_pin_write_logic(const pin_config_t*_pin_config,Logic_t logic)
{
  Std_ReturnType ret =E_OK;
    if(NULL == _pin_config|| _pin_config->pin >PORT_PIN_MAX_NUMBRE-1)
        ret=E_NOT_OK;
    else 
    {
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            default :ret = E_NOT_OK ;

        }
    }   
    
  return ret;    
    
}
Std_ReturnType gpio_pin_read_logic(const pin_config_t*_pin_config,Logic_t *logic)
{
      Std_ReturnType ret =E_OK;
     if(NULL == _pin_config || NULL == logic|| _pin_config->pin >PORT_PIN_MAX_NUMBRE-1)
        ret=E_NOT_OK;
    else
    {
        *logic=READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);

    }
        
        return ret;
    
}
Std_ReturnType gpio_pin_intialize(const pin_config_t*_pin_config)
{
   Std_ReturnType ret =E_OK;
  if(NULL == _pin_config|| _pin_config->pin >PORT_PIN_MAX_NUMBRE-1)
        ret=E_NOT_OK;
    else 
    {
      gpio_pin_direction_intialize(_pin_config);
      gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }   
    return ret;  

}

