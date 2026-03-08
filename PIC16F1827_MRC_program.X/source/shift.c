/*
 * File:   main.c
 * Author: ICE_MEGANE
 *
 * Created on 2020/03/5, 22:26
 */

#include <xc.h>

#include "userdefine.h"

#include "shift.h"

#include "./mcufunc/gpio.h"
#include "./tools/servo.h"


#define SERVO_POSI_NEUTRAL        SERVO_ANGLE__30DEG
#define SERVO_POSI_LOWER          SERVO_ANGLE__15DEG
#define SERVO_POSI_UPPER          SERVO_ANGLE__45DEG

/* シフトチェンジの制御を担当 */

/* 関数プロトタイプ宣言 */
static void func_shift_s_shift_change( void );




/* グローバル変数 */
/**************************************************************/
/*  Function:                                                 */
/*  main関数                                                   */
/*                                                            */
/*                                                            */
/**************************************************************/
void func_shift_g_main( void )
{
    func_shift_s_shift_change();
}


/**************************************************************/
/*  Function:                                                 */
/*  初期化関数                                                 */
/*                                                            */
/*                                                            */
/**************************************************************/
void func_shift_g_init( void )
{
    ;
}


/**************************************************************/
/*  Function:                                                 */
/*  関数                                                 */
/*                                                            */
/*                                                            */
/**************************************************************/
static void func_shift_s_shift_posi_adjust( void )
{
    ;
}


/**************************************************************/
/*  Function:                                                 */
/*  関数                                                 */
/*                                                            */
/*                                                            */
/**************************************************************/
static void func_shift_s_shift_change( void )
{
    /* シフトポジション指定 */
    if( ts_gpio_g_in_neutral.u8_state == SET )
    {
        /* サーボ上下に固定 */
        if( ts_gpio_g_in_shift_0.u8_state == SET )
        {
            servo_s_angle_set( SERVO_POSI_UPPER, SERVO_SHIFT_0 );
        }
        else
        {
            servo_s_angle_set( SERVO_POSI_LOWER, SERVO_SHIFT_0 );
        }


        if( ts_gpio_g_in_shift_1.u8_state == SET )
        {
            servo_s_angle_set( SERVO_POSI_UPPER, SERVO_SHIFT_1 );
        }
        else
        {
            servo_s_angle_set( SERVO_POSI_LOWER, SERVO_SHIFT_1 );
        }


        if( ts_gpio_g_in_shift_2.u8_state == SET )
        {
            servo_s_angle_set( SERVO_POSI_UPPER, SERVO_SHIFT_2 );
        }
        else
        {
            servo_s_angle_set( SERVO_POSI_LOWER, SERVO_SHIFT_2 );
        }
    }
    else
    {
        /* サーボ 中立 */
        servo_s_angle_set( SERVO_POSI_NEUTRAL, SERVO_SHIFT_0 );
        servo_s_angle_set( SERVO_POSI_NEUTRAL, SERVO_SHIFT_1 );
        servo_s_angle_set( SERVO_POSI_NEUTRAL, SERVO_SHIFT_2 );
    }
}

