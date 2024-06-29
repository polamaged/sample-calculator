#include "application.h"
Std_ReturnType ret = E_OK;  

sint8 ret_val_from_kpad = -1;

uint8 temp_number = 0;
uint8 answer_numebr = 0;
uint8 last_char = '0';

uint8  final_answer[11];

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();

    ret = lcd_4bit_send_command(&lcd, _LCD_CURSOR_ON_BLINK_OFF);
    
    while(1){
        ret = keypad_get_value(&keypad , &ret_val_from_kpad);
        __delay_ms(150);
        if(ret_val_from_kpad == '#'){
            ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR); 
            ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
            ret_val_from_kpad = -1;
            temp_number = 0;
            answer_numebr = 0;
            last_char = '0';
            ret = lcd_4bit_send_string_position(&lcd , 1 , 6 , "WELCOME");
            __delay_ms(1000);
            ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
        }
        if(ret_val_from_kpad != -1){
            ret = lcd_4bit_send_char_data(&lcd , ret_val_from_kpad);
            
            if(ret_val_from_kpad>='0' && ret_val_from_kpad<='9'){
                temp_number*=10;
                temp_number+=(ret_val_from_kpad-'0');
            }
            else{
                //12 + 12 - 2 = 22 + 
                if(last_char == '0'){
                    answer_numebr=temp_number;
                    if(ret_val_from_kpad == '+'){
                        last_char='+';
                    }
                    else if(ret_val_from_kpad == '-'){
                        last_char='-';
                    }
                    else if(ret_val_from_kpad == '*'){
                        last_char='*';
                    }
                    else if(ret_val_from_kpad == '/'){
                        last_char='/';
                    }
                }
                
                else if(last_char == '+'){
                    answer_numebr+=temp_number;
                    last_char = ret_val_from_kpad;
                }
                else if(last_char == '-'){
                    answer_numebr-=temp_number;
                    last_char = ret_val_from_kpad;
                }
                else if(last_char == '*'){
                    answer_numebr*=temp_number;
                    last_char = ret_val_from_kpad;
                }
                else if(last_char == '/'){
                    answer_numebr/=temp_number;
                    last_char = ret_val_from_kpad;
                }
                
                
                
                if(ret_val_from_kpad == '='){
                    ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                    ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
                    ret = convert_int_to_string(answer_numebr, final_answer);
                    ret = lcd_4bit_send_string(&lcd , final_answer);
                }
                
                temp_number = 0;
            }
            
            ret_val_from_kpad = -1;
        }
        
        
        
    }
    
    return (EXIT_SUCCESS);
}
void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd);
    ret = keypad_initialize(&keypad);
}
