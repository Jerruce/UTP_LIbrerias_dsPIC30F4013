

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_timer.h"

/* Definición de macros */

#define TRIS_LED1   TRISDbits.TRISD0
#define TRIS_LED2   TRISDbits.TRISD1
#define TRIS_LED3   TRISDbits.TRISD2

#define LAT_LED1   LATDbits.LATD0
#define LAT_LED2   LATDbits.LATD1
#define LAT_LED3   LATDbits.LATD2

/* Declaración de funciones */
void Timer1_Initialize(void);
void Timer2_Initialize(void);
void Timer3_Initialize(void);

/* Función principal */
int main(void)
{
    /* Configurar los pines de los LEDs como salida*/
    TRIS_LED1 = 0;
    TRIS_LED2 = 0;
    TRIS_LED3 = 0;
    
    /* Configurar el Timer1 para contar 500 ms */
    Timer1_Initialize();
    /* Configurar el Timer2 para contar 250 ms */
    Timer2_Initialize();
    /* Configurar el Timer3 para contar 100 ms */
    Timer3_Initialize();
    
    while(1)
    {
        /* Conmutar el LED1 cada 500 ms*/
        if(IFS0bits.T1IF == 1)
        {
           IFS0bits.T1IF = 0;
           LAT_LED1 = !LAT_LED1;
        }
        
        /* Conmutar el LED2 cada 250 ms*/
        if(IFS0bits.T2IF == 1)
        {
           IFS0bits.T2IF = 0;
           LAT_LED2 = !LAT_LED2;
        }     
        
        /* Conmutar el LED3 cada 100 ms*/
        if(IFS0bits.T3IF == 1)
        {
           IFS0bits.T3IF = 0;
           LAT_LED3 = !LAT_LED3;
        }   
    }
    
    return 0;
}


/* Definición de funciones */
void Timer1_Initialize(void)
{
    timer_a_t timer1;
    
    timer1.timer_status = TIMER_ON;
    timer1.clock_source = TIMER_INTERNAL_CLOCK;
    timer1.prescaler = TIMER_PRESCALER_256;
    timer1.ext_clk_sync = TIMER_EXT_CLK_SYNC_DISABLED;
    timer1.gated_time_accum = TIMER_GATED_TIME_ACCUMULATION_DISABLED;
    timer1.stop_idle = TIMER_CONTINUE_IN_IDLE_MODE;
    timer1.top_value = 46874;
    timer1.match_interrupt = TIMER_INTERRUPT_DISABLED;
    
    Timer1_Configure(&timer1);
}

void Timer2_Initialize(void)
{
    timer_b_t timer2;
    
    timer2.timer_status = TIMER_ON;
    timer2.clock_source = TIMER_INTERNAL_CLOCK;
    timer2.prescaler = TIMER_PRESCALER_256;
    timer2.concatenation = TIMER_X_AND_TIMER_Y_SEPARATE;
    timer2.gated_time_accum = TIMER_GATED_TIME_ACCUMULATION_DISABLED;
    timer2.stop_idle = TIMER_CONTINUE_IN_IDLE_MODE;
    timer2.top_value = 23437;
    timer2.match_interrupt = TIMER_INTERRUPT_DISABLED;
    
    Timer2_Configure(&timer2);  
}

void Timer3_Initialize(void)
{
    timer_c_t timer3;
    
    timer3.timer_status = TIMER_ON;
    timer3.clock_source = TIMER_INTERNAL_CLOCK;
    timer3.prescaler = TIMER_PRESCALER_256;
    timer3.gated_time_accum = TIMER_GATED_TIME_ACCUMULATION_DISABLED;
    timer3.stop_idle = TIMER_CONTINUE_IN_IDLE_MODE;
    timer3.top_value = 9374;
    timer3.match_interrupt = TIMER_INTERRUPT_DISABLED;
    
    Timer3_Configure(&timer3);      
    
}