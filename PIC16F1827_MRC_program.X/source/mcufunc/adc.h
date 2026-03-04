/* 
 * File:   adc.h
 * Author: shunt
 *
 * Created on 2026/03/04, 22:26
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

/*********************************************************************************************************************/
/* AD変換チャネル定義 */
#define ADC_AN0     ((u8)0)
#define ADC_AN1     ((u8)1)
#define ADC_AN2     ((u8)2)
#define ADC_AN3     ((u8)3)
#define ADC_AN4     ((u8)4)
#define ADC_AN5     ((u8)5)
#define ADC_AN6     ((u8)6)
#define ADC_AN7     ((u8)7)
#define ADC_AN8     ((u8)8)
#define ADC_AN9     ((u8)9)
#define ADC_AN10    ((u8)10)
#define ADC_AN11    ((u8)11)
#define ADC_CH_NUM  (ADC_AN11+(u8)1)

#define ADC_REQ     ((u8)0)
#define ADC_RESULT  ((u8)1)
#define ADC_DATA_SELECT (ADC_RESULT + (u8)1)


/* 変換時間 */
#define ADC_ACQUISION_TIME      ((u8)20)


/* 関数宣言 */
extern void func_adc_g_main( void );                       /* AD変換処理 メインループ用 */
extern void func_adc_g_init( void );                       /* AD変換処理 変数初期化 */
extern void func_adc_g_adc_data_get( void );               /* AD変換結果 取得処理 割り込み処理用 */


/*********************************************************************************************************************/
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

