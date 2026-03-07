/* 
 * File:   servo.h
 * Author: shunt
 *
 * Created on 2026/03/04, 22:56
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif


/* サーボ番号指定 */
#define SERVO_SHIFT_0               ((u8)0)
#define SERVO_SHIFT_1               ((u8)1)
#define SERVO_SHIFT_2               ((u8)2)

/* サーボ角度テーブル index */
#define SERVO_DEG___0               (u8)0U
#define SERVO_DEG___5               (u8)1U
#define SERVO_DEG__10               (u8)2U
#define SERVO_DEG__15               (u8)3U
#define SERVO_DEG__20               (u8)4U
#define SERVO_DEG__25               (u8)5U
#define SERVO_DEG__30               (u8)6U
#define SERVO_DEG__35               (u8)7U
#define SERVO_DEG__40               (u8)8U
#define SERVO_DEG__45               (u8)9U
#define SERVO_DEG__50               (u8)10U
#define SERVO_DEG__55               (u8)11U
#define SERVO_DEG__60               (u8)12U
#define SERVO_DEG__65               (u8)13U
#define SERVO_DEG__70               (u8)14U
#define SERVO_DEG__75               (u8)15U
#define SERVO_DEG__80               (u8)16U
#define SERVO_DEG__85               (u8)17U
#define SERVO_DEG__90               (u8)18U
#define SERVO_DEG__95               (u8)19U
#define SERVO_DEG__100              (u8)20U
#define SERVO_DEG__105              (u8)21U
#define SERVO_DEG__110              (u8)22U
#define SERVO_DEG__115              (u8)23U
#define SERVO_DEG__120              (u8)24U
#define SERVO_DEG__125              (u8)25U
#define SERVO_DEG__130              (u8)26U
#define SERVO_DEG__135              (u8)27U
#define SERVO_DEG__140              (u8)28U
#define SERVO_DEG__145              (u8)29U
#define SERVO_DEG__150              (u8)30U
#define SERVO_DEG__155              (u8)31U
#define SERVO_DEG__160              (u8)32U
#define SERVO_DEG__165              (u8)33U
#define SERVO_DEG__170              (u8)34U
#define SERVO_DEG__175              (u8)35U
#define SERVO_DEG__180              (u8)36U
#define SERVO_DEG__MAX              SERVO_DEG__180
#define SERVO_ANGLE_NUM             ((u8)SERVO_DEG__MAX + (u8)1)


extern void servo_s_angle_set( u8 u8_angle_idx, u8 servo_num );

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

