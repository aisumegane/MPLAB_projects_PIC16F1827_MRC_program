/* PIC16F1827 Configuration Bit Settings */

/* 'C' source line config statements */

/* CONFIG1 */
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

/* CONFIG2 */
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

/* #pragma config statements should precede project file includes. */
/* Use project enums instead of #define for ON and OFF. */

/*==========================================================================================================================================*/



/*
 * File:   main.c
 * Author: ICE_MEGANE
 *
 * Created on 2020/03/5, 22:26
 */

#include <xc.h>


/* 追加インクルード*/
/* mcufuncフォルダ */
#include "./mcufunc/adc.h"
#include "./mcufunc/int.h"
#include "./mcufunc/mcu_setup.h"

/* usertoolsフォルダ */

/* 同一階層 */
#include "userdefine.h"


/* 関数プロトタイプ宣言 */
static void func_main_s_init( void );
static void func_main_s_program_start( void );
static void func_main_s_loop( void );


/* 変数宣言 */
static u8 u8_main_s_loop_go;
static u8 u8_main_s_10ms_task_flag;


/**************************************************************/
/*  Function:                                                 */
/*  main task                                                 */
/*                                                            */
/**************************************************************/
void main(void)
{   
    func_mset_g_main();                     /* マイコン初期化 */
    func_main_s_init();                     /* 変数初期化 */
    func_mset_g_mcu_start_condition();      /* プログラム開始状態 */

    while( 1 )
    { /* 20ms 周期タスク */
        if( u8_main_s_loop_go == SET )
        {
            func_main_s_loop();
            u8_main_s_loop_go = CLEAR;
        }
    }
}


/**************************************************************/
/*  Function:                                                 */
/*  mainループ動作許可フラグ 設定関数                            */
/*                                                            */
/**************************************************************/
void  func_main_s_main_loop_judge( void )
{
    u8_main_s_loop_go = SET;
}


/*******************/
/* static function */
/*******************/
/**************************************************************/
/*  Function:                                                 */
/*  メインループ処理                                           */
/*                                                            */
/**************************************************************/
static void func_main_s_loop( void )
{
    /* テスト出力 */
    /* 10ms感覚で出力反転 */
    if( u8_main_s_10ms_task_flag == CLEAR )
    {
        u8_main_s_10ms_task_flag = SET;
        LATA |= 0x02U;          /* RA1 : HI */
    }
    else
    {
        u8_main_s_10ms_task_flag = CLEAR;
        LATA &= (u8)~0x02U;     /* RA1 : LOW */
    }


    /* 関数コール */
    func_adc_g_main();          /* AD変換処理　 */
    func_int_g_main();          /* 割り込み処理 */
}


/**************************************************************/
/*  Function:                                                 */
/*  変数初期設定                                               */
/*                                                            */
/**************************************************************/
static void func_main_s_init( void )
{
    u8_main_s_loop_go = CLEAR;
    u8_main_s_10ms_task_flag = CLEAR;
    
    /* ファイルの並び順に整列 */
    func_adc_g_init();
    func_int_g_init();
}





