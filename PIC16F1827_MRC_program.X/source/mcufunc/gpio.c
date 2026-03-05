/*
 * File:   main.c
 * Author: ICE_MEGANE
 *
 * Created on 2020/03/5, 22:26
 */

#include <xc.h>
#include "pic16F1827.h"

#include "./userdefine.h"

#include "gpio.h"


#define GPIO_PORT_IN_JUDGE_CNT      ((u8)2)



ts_gpio_in_def ts_gpio_g_in_shift_0;
ts_gpio_in_def ts_gpio_g_in_shift_1;
ts_gpio_in_def ts_gpio_g_in_shift_2;
ts_gpio_in_def ts_gpio_g_in_neutral;


static const ts_gpio_in_def ts_gpio_s_in_init =
{
    (u8)0,
    (u8)0,
    (u8)0
};


u8 u8_gpio_g_out_7seg_led_data_a;
u8 u8_gpio_g_out_7seg_led_data_b;
u8 u8_gpio_g_out_7seg_led_data_c;
u8 u8_gpio_g_out_7seg_led_data_d;


/* 関数プロトタイプ宣言 */
static void func_gpio_s_in_judge( void );
static void func_gpio_s_out_update( void );
static void func_gpio_s_port_judge( ts_gpio_in_def ts_port, u8 port_in );


/* グローバル変数 */
/**************************************************************/
/*  Function:                                                 */
/*  main関数                                                   */
/*                                                            */
/*                                                            */
/**************************************************************/
void func_gpio_g_main( void )
{
    func_gpio_s_in_judge();         /* 入力ポート判定更新 */
    func_gpio_s_out_update();       /* 出力ポート更新 */
}


/**************************************************************/
/*  Function:                                                 */
/*  gpio初期化関数                                             */
/*                                                            */
/*                                                            */
/**************************************************************/
void func_gpio_g_init( void )
{
    ts_gpio_g_in_shift_0 = ts_gpio_s_in_init;           /* 初回はソフト判定OFFから開始 */
    ts_gpio_g_in_shift_1 = ts_gpio_s_in_init;
    ts_gpio_g_in_shift_2 = ts_gpio_s_in_init;
    ts_gpio_g_in_neutral = ts_gpio_s_in_init;
    
    u8_gpio_g_out_7seg_led_data_a = CLEAR;
    u8_gpio_g_out_7seg_led_data_b = CLEAR;
    u8_gpio_g_out_7seg_led_data_c = CLEAR;
    u8_gpio_g_out_7seg_led_data_d = CLEAR;
}


/**************************************************************/
/*  Function:                                                 */
/*  ポート入力判定関数                                          */
/*                                                            */
/**************************************************************/
static void func_gpio_s_in_judge( void )
{
    func_gpio_s_port_judge( ts_gpio_g_in_neutral, (u8)RB0 );
    func_gpio_s_port_judge( ts_gpio_g_in_shift_0, (u8)RB1 );
    func_gpio_s_port_judge( ts_gpio_g_in_shift_1, (u8)RB2 );
    func_gpio_s_port_judge( ts_gpio_g_in_shift_2, (u8)RB3 );
}



/**************************************************************/
/*  Function:                                                 */
/*  ポート出力設定関数                                          */
/*  出力切り替えはすべてこの処理呼び出し時に実行する               */
/**************************************************************/
static void func_gpio_s_out_update( void )
{
    LATB5 = u8_gpio_g_out_7seg_led_data_a;
    LATA1 = u8_gpio_g_out_7seg_led_data_b;
    LATA0 = u8_gpio_g_out_7seg_led_data_c;
    LATA6 = u8_gpio_g_out_7seg_led_data_d;
}



/**************************************************************/
/*  Function:                                                 */
/*  ポート入力関数                                             */
/*                                                            */
/*                                                            */
/**************************************************************/
static void func_gpio_s_port_judge( ts_gpio_in_def ts_port, u8 port_in )
{   
    if( ts_port.u8_buff != port_in )
    { /* 前回とポート状態が違う */
        ts_port.u8_judge_cnt = (u8)0;
    }
    
    if( ts_port.u8_judge_cnt > GPIO_PORT_IN_JUDGE_CNT )
    { /* n回連続でポート状態が同じ */
        ts_port.u8_state = port_in;
    }
}



