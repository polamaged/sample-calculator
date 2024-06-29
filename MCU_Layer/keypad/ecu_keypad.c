#include "ecu_keypad.h"


static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLOUMNS] = {
                                                                {'7','8','9','/'},
                                                                {'4','5','6','*'},
                                                                {'1','2','3','-'},
                                                                {'#','0','=','+'},
                                                            };

Std_ReturnType keypad_initialize (const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0;
    if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0 ; rows_counter < KEYPAD_ROWS ; rows_counter++){
            ret = gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0 ; columns_counter < KEYPAD_COLOUMNS ; columns_counter++){
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}


//Std_ReturnType keypad_get_value  (const keypad_t *_keypad_obj, uint8 *value){
//    Std_ReturnType ret = E_OK;
//    uint8 l_rows_counter = 0 , l_columns_counter = 0 , l_counter = 0;
//    uint8 coulomn_logic = 0;
//    if((NULL == _keypad_obj) && (NULL == value)){
//        ret = E_NOT_OK;
//    }
//    else{
//        for(l_rows_counter = 0 ; l_rows_counter < 0 ; l_rows_counter++){
//            for(l_counter = 0 ; l_counter < KEYPAD_ROWS ; l_counter++){
//               ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]) , GPIO_LOW);
//            }
//            gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]) , GPIO_HIGH);
//            __delay_ms(10);
//            for(l_columns_counter = 0 ; l_columns_counter < KEYPAD_COLOUMNS ; l_columns_counter++){
//                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]) , &coulomn_logic);
//                if(GPIO_HIGH == coulomn_logic){
//                    *value = btn_values[l_rows_counter][l_columns_counter];
//                }
//            }
//        }
//    }
//    return ret;
//}

Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != keypad && NULL != value){
        ret = E_OK;
        Logic_t logic = 0;
        uint8 keypad_pressed = 0;
        for(uint8 rows = 0 ; rows < KEYPAD_ROWS ; rows++){
            ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[rows]), GPIO_HIGH);
            for(uint8 col = 0 ; col < KEYPAD_COLOUMNS ; col++){
                ret = gpio_pin_read_logic(&(keypad->keypad_columns_pins[col]), &logic);
                if(GPIO_HIGH == logic){
                    *value = btn_values[rows][col];
                    keypad_pressed = 1;
                    break;
                }
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[rows]), GPIO_LOW);
            if(keypad_pressed){
                break;
            }
        }
    }
    return ret;
}