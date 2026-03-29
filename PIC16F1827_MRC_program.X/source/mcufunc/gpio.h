/* 
 * File:   int.h
 * Author: unko
 *
 * Created on 2026/03/05, 22:40
 */

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct gpio_in
{
    u8 u8_judge_cnt;
    u8 u8_buff;
    u8 u8_state;
    u8 u8_state_bf;
}gpio_in;

extern void func_gpio_g_main( void );
extern void func_gpio_g_init( void );


extern gpio_in ts_gpio_g_in_shift_0;
extern gpio_in ts_gpio_g_in_shift_1;
extern gpio_in ts_gpio_g_in_shift_2;
extern gpio_in ts_gpio_g_in_neutral;

extern u8 u8_gpio_g_out_7seg_led_data_a;
extern u8 u8_gpio_g_out_7seg_led_data_b;
extern u8 u8_gpio_g_out_7seg_led_data_c;
extern u8 u8_gpio_g_out_7seg_led_data_d;



#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */