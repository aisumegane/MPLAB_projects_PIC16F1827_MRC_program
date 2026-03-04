
/*
 * File:   main.c
 * Author: ICE_MEGANE
 *
 * Created on 2020/03/5, 22:26
 */

#include <xc.h>
#include "./userdefine.h"

#include "adc.h"
 
 
/* 関数プロトタイプ宣言 */
static void func_adc_s_convert_start(u8 adc_ch);               /* AD変換 開始処理 */
 
 /* AD変換要求 保持用配列 */
static u8 u8_main_s_adc_req_status[ ADC_CH_NUM ] =
{ /* AD変換チャネルが数値と1対1なので、配列の要素指定にそのまま使える */
    (u8)0, (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0,  (u8)0
};

/* AD変換結果 保持用配列 */
static u16 u16_main_s_adc_result[ ADC_CH_NUM ] =
{
    (u16)0, (u16)0, (u16)0, (u16)0,  (u16)0, (u16)0, (u16)0, (u16)0,  (u16)0, (u16)0, (u16)0, (u16)0
};



/* グローバル関数 */
/**************************************************************/
/*  Function:                                                 */
/*  AD変換実行処理　                                           */
/*                                                            */
/**************************************************************/
void func_adc_g_main( void )
{
    /* AD変換結果取得 */

    /* 次のAD変換開始処理 */
    func_adc_s_convert_start( ADC_AN2 );
    func_adc_s_convert_start( ADC_AN3 );
}


/**************************************************************/
/*  Function:                                                 */
/*  AD変換実行処理　                                           */
/*                                                            */
/**************************************************************/
void func_adc_g_init( void )
{
    u8 u8_loopcnt;
    
    for( u8_loopcnt = (u8)0; u8_loopcnt < ADC_CH_NUM; u8_loopcnt++ )
    {
        u8_main_s_adc_req_status[ u8_loopcnt ] = (u8)0;
        u16_main_s_adc_result[ u8_loopcnt ]    = (u16)0;
    }
}




/* 静的関数 */
/**************************************************************/
/*  Function:                                                 */
/*  AD変換開始要求処理                                         */
/*                                                            */
/**************************************************************/
static void func_adc_s_convert_start(u8 adc_ch)
{
    u8 u8_adc_wait;
    u8 u8_setting_buff;
    u8 u8_adc_now_process;

    u8_main_s_adc_req_status[ adc_ch ] = SET;       /* AD変換要求を格納する */

    u8_adc_now_process = ADCON0;
    
    if( ( u8_adc_now_process & (u8)0x02 ) == (u8)0 )
    { /* 現在実行中のAD変換がない = 最初の1回目の変換待ち状態 */
        u8_setting_buff = (u8)( adc_ch << 2U );     /* CHSは6~2bit目なので、下2bit分シフトする */
        ADCON0 &= ((u8)~0x7C);              /* CHSビットをいったんすべてクリア */
        ADCON0 |= u8_setting_buff;          /* 今回変換したい */

        /* AD変換の対象チャネル切り替え後はアクイジョン・タイムを設ける */
        /* 短すぎるとサンプルホールド用コンデンサの充電が足りず、AD変換結果が期待値より下がるので注意 */
        u8_adc_wait = ADC_ACQUISION_TIME;
        while( u8_adc_wait > (u8)0 )
        {
            u8_adc_wait--;
        }

        ADCON0 |= (u8)0x02;     /* GO_nDONE = SET：ADC開始 (完了後は自動クリアされる) */
    }

    /* ここで変換要求を出して以降、割り込み内でこの関数を再度呼び出し、自動で連続処理する */
}

/**************************************************************/
/*  Function:                                                 */
/*  AD変換 値取得処理                                          */
/*                                                            */
/**************************************************************/
void func_adc_g_adc_data_get( void )
{
    u8 u8_adc_ch;
    u8 u8_loopcnt;
    u16 u16_adc_result;

    /* 現在のAD変換対象の取得(この処理自体が割り込みで呼ばれる=初回の変換は完了している地点からスタート) */
    u8_adc_ch = ADCON0;
    u8_adc_ch = u8_adc_ch & (u8)0x7C;       /* ビットマスク:0b0111-1100 */
    u8_adc_ch = u8_adc_ch >> 2U;            /* CHSのデータを2bit下位シフトして数値として使えるようにする */

    /* AD変換結果の取得 */
    u16_adc_result = (u16)ADRESH;
    u16_adc_result = u16_adc_result << 8U;              /* 上位データを8ビット上へ移動　※データはLSB詰めで取得している */
    u16_adc_result += (u16)ADRESL;                           /* 下位データはそのまま加算する */

    u16_main_s_adc_result[ u8_adc_ch ] = u16_adc_result;    /* AD変換結果取得 */
    u8_main_s_adc_req_status[ u8_adc_ch ] = CLEAR;          /* 変換要求クリア */

    /* AD変換未完了CHの検索 */
    for( u8_loopcnt = (u8)0; u8_loopcnt < ADC_CH_NUM; u8_loopcnt++ )
    { /* AD変換要求が連続して発生 = 渋滞している場合への対応 */
        if( u8_main_s_adc_req_status[ u8_loopcnt ] == SET )
        { /* AD変換要求があるチャネルを発見 */
            break;
        }
    }

    /* 次のAD変換実行 */
    if( u8_loopcnt < ADC_CH_NUM )
    { /* 少なくとも1chの未完了-変換要求が残っている。 */
        func_adc_s_convert_start( u8_loopcnt );
    }
}

















