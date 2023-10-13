/* 
 * File:   MT_timer.h
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 10:27 AM
 */

#ifndef MT_TIMER_H
#define	MT_TIMER_H

/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>

/* Definición de tipos */

typedef enum
{
    TIMER_OFF = 0,
    TIMER_ON
}
timer_status_t;


typedef enum
{
    TIMER_CONTINUE_IN_IDLE_MODE = 0,
    TIMER_STOP_IN_IDLE_MODE        
}
timer_stop_idle_t;


typedef enum
{
    TIMER_GATED_TIME_ACCUMULATION_DISABLED = 0,
    TIMER_GATED_TIME_ACCUMULATION_ENABLED       
}
timer_gated_time_accum_t;

   
typedef enum
{
    TIMER_INTERNAL_CLOCK = 0,
    TIMER_EXTERNAL_CLOCK
}
timer_clock_source_t;


typedef enum
{
    TIMER_PRESCALER_1 = 0,
    TIMER_PRESCALER_8,
    TIMER_PRESCALER_64,
    TIMER_PRESCALER_256
}
timer_prescaler_t;


typedef enum
{
    TIMER_EXT_CLK_SYNC_DISABLED = 0,
    TIMER_EXT_CLK_SYNC_ENABLED
}
timer_a_ext_clk_sync_t;

typedef enum
{
    TIMER_X_AND_TIMER_Y_SEPARATE = 0,
    TIMER_X_AND_TIMER_Y_CONCATENATE
}
timer_b_concatenation_t;


typedef enum
{
    TIMER_INTERRUPT_DISABLED = 0,
    TIMER_INTERRUPT_ENABLED        
}
timer_interrupt_status_t;


typedef struct
{
    uint16_t top_value;
    timer_status_t timer_status;
    timer_stop_idle_t stop_idle;
    timer_gated_time_accum_t gated_time_accum;
    timer_prescaler_t prescaler;
    timer_a_ext_clk_sync_t ext_clk_sync;
    timer_clock_source_t clock_source;
    timer_interrupt_status_t match_interrupt;
}
timer_a_t;


typedef struct
{
    uint16_t top_value;
    timer_status_t timer_status;
    timer_stop_idle_t stop_idle;
    timer_gated_time_accum_t gated_time_accum;
    timer_prescaler_t prescaler;
    timer_b_concatenation_t concatenation;
    timer_clock_source_t clock_source;
    timer_interrupt_status_t match_interrupt;
}
timer_b_t;


typedef struct
{
    uint16_t top_value;
    timer_status_t timer_status;
    timer_stop_idle_t stop_idle;
    timer_gated_time_accum_t gated_time_accum;
    timer_prescaler_t prescaler;
    timer_clock_source_t clock_source;
    timer_interrupt_status_t match_interrupt;
}
timer_c_t;


/* Declaración de funciones */
void Timer1_Configure(timer_a_t *timer_param);
void Timer2_Configure(timer_b_t *timer_param);
void Timer3_Configure(timer_c_t *timer_param);
void Timer4_Configure(timer_b_t *timer_param);
void Timer5_Configure(timer_c_t *timer_param);

#endif	/* MT_TIMER_H */