
/* Inclusión de archivos */
#include "MT_timer.h"

/* Definición de funciones */

void Timer1_Configure(timer_a_t *timer_param)
{
    /* Inicializar el registro*/
    T1CON = 0;
    
    /* PASO 1: Desactivar el Timer */
    T1CONbits.TON = 0;
    
    /* PASO 2: Indicar si el Timer trabajará o no en el estado IDLE */
    if(timer_param->stop_idle == TIMER_STOP_IN_IDLE_MODE)
    {
        T1CONbits.TSIDL = 1;
    }
    else
    {
        T1CONbits.TSIDL = 0;
    }
    
    /* PASO 2: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER_EXTERNAL_CLOCK)
    {
        T1CONbits.TCS = 1;    
    }
    else
    {
        T1CONbits.TCS = 0;    
    }
    
    /* PASO 3: Configurar la sincronización con el clock externo */
    if(timer_param->ext_clk_sync == TIMER_EXT_CLK_SYNC_ENABLED)
    {
        T1CONbits.TSYNC = 1;
    }
    else
    {
        T1CONbits.TSYNC = 0;
    }
    
    /* PASO 4: Configurar la acumulación de tiempo */
    if(timer_param->gated_time_accum == TIMER_GATED_TIME_ACCUMULATION_ENABLED )
    {
        T1CONbits.TGATE = 1;
    }
    else
    {
        T1CONbits.TGATE = 0;
    }    
    
    /* PASO 5: Configurar el Pre-Scaler */
    T1CONbits.TCKPS = timer_param->prescaler & 0b00000011; 
    
    /* PASO 6: Cargar el valor TOP (PRx) */
    PR1 = timer_param->top_value;
    
    /* PASO 7: Activar el Timer de ser el caso */
    if(timer_param->timer_status == TIMER_ON)
    {
        T1CONbits.TON = 1;    
    }
    else
    {
        T1CONbits.TON = 0;
    }
  
    /* PASO 8: Activar la interrupción por comparación, de ser el caso */
    if(timer_param->match_interrupt == TIMER_INTERRUPT_ENABLED)
    {
        IEC0bits.T1IE = 1;
    }
    else
    {
        IEC0bits.T1IE = 0;
    }
    
}


void Timer2_Configure(timer_b_t *timer_param)
{
     /* Inicializar el registro*/
    T2CON = 0;
    
    /* PASO 1: Desactivar el Timer */
    T2CONbits.TON = 0;
    
     /* PASO 2: Indicar si el Timer trabajará o no en el estado IDLE */
    if(timer_param->stop_idle == TIMER_STOP_IN_IDLE_MODE)
    {
        T2CONbits.TSIDL = 1;
    }
    else
    {
        T2CONbits.TSIDL = 0;
    }   
    
    /* PASO 3: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER_EXTERNAL_CLOCK)
    {
        T2CONbits.TCS = 1;    
    }
    else
    {
        T2CONbits.TCS = 0;    
    }
    
    /* PASO 4: Concatenar dos timers, de ser el caso */
    if(timer_param->concatenation == TIMER_X_AND_TIMER_Y_CONCATENATE)
    {
        T2CONbits.T32 = 1;
    }
    else
    {
        T2CONbits.T32 = 0;
    }
    
    /* PASO 5: Configurar la acumulación de tiempo */
    if(timer_param->gated_time_accum == TIMER_GATED_TIME_ACCUMULATION_ENABLED )
    {
        T2CONbits.TGATE = 1;
    }
    else
    {
        T2CONbits.TGATE = 0;
    }    
    
    /* PASO 6: Configurar el Pre-Scaler */
    T2CONbits.TCKPS = timer_param->prescaler & 0b00000011; 
    
    /* PASO 7: Cargar el valor TOP (PRx) */
    PR2 = timer_param->top_value;
    
    /* PASO 8: Activar el Timer de ser el caso */
    if(timer_param->timer_status == TIMER_ON)
    {
        T2CONbits.TON = 1;    
    }
    else
    {
        T2CONbits.TON = 0;
    }
  
    /* PASO 8: Activar la interrupción por comparación, de ser el caso */
    if(timer_param->match_interrupt == TIMER_INTERRUPT_ENABLED)
    {
        IEC0bits.T2IE = 1;
    }
    else
    {
        IEC0bits.T2IE = 0;
    }   
}

void Timer3_Configure(timer_c_t *timer_param)
{
    /* Inicializar el registro*/
    T3CON = 0;
    
    /* PASO 1: Desactivar el Timer */
    T3CONbits.TON = 0;
 
    /* PASO 2: Indicar si el Timer trabajará o no en el estado IDLE */
    if(timer_param->stop_idle == TIMER_STOP_IN_IDLE_MODE)
    {
        T3CONbits.TSIDL = 1;
    }
    else
    {
        T3CONbits.TSIDL = 0;
    }    
    
    /* PASO 3: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER_EXTERNAL_CLOCK)
    {
        T3CONbits.TCS = 1;    
    }
    else
    {
        T3CONbits.TCS = 0;    
    }
    
    /* PASO 4: Configurar la acumulación de tiempo */
    if(timer_param->gated_time_accum == TIMER_GATED_TIME_ACCUMULATION_ENABLED )
    {
        T3CONbits.TGATE = 1;
    }
    else
    {
        T3CONbits.TGATE = 0;
    }    
    
    /* PASO 5: Configurar el Pre-Scaler */
    T3CONbits.TCKPS = timer_param->prescaler & 0b00000011; 
    
    /* PASO 6: Cargar el valor TOP (PRx) */
    PR3 = timer_param->top_value;
    
    /* PASO 7: Activar el Timer de ser el caso */
    if(timer_param->timer_status == TIMER_ON)
    {
        T3CONbits.TON = 1;    
    }
    else
    {
        T3CONbits.TON = 0;
    }
  
    /* PASO 8: Activar la interrupción por comparación, de ser el caso */
    if(timer_param->match_interrupt == TIMER_INTERRUPT_ENABLED)
    {
        IEC0bits.T3IE = 1;
    }
    else
    {
        IEC0bits.T3IE = 0;
    }    
}

void Timer4_Configure(timer_b_t *timer_param)
{
     /* Inicializar el registro*/
    T4CON = 0;
    
    /* PASO 1: Desactivar el Timer */
    T4CONbits.TON = 0;
    
     /* PASO 2: Indicar si el Timer trabajará o no en el estado IDLE */
    if(timer_param->stop_idle == TIMER_STOP_IN_IDLE_MODE)
    {
        T4CONbits.TSIDL = 1;
    }
    else
    {
        T4CONbits.TSIDL = 0;
    }   
    
    /* PASO 3: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER_EXTERNAL_CLOCK)
    {
        T4CONbits.TCS = 1;    
    }
    else
    {
        T4CONbits.TCS = 0;    
    }
    
    /* PASO 4: Concatenar dos timers, de ser el caso */
    if(timer_param->concatenation == TIMER_X_AND_TIMER_Y_CONCATENATE)
    {
        T4CONbits.T32 = 1;
    }
    else
    {
        T4CONbits.T32 = 0;
    }
    
    /* PASO 5: Configurar la acumulación de tiempo */
    if(timer_param->gated_time_accum == TIMER_GATED_TIME_ACCUMULATION_ENABLED )
    {
        T4CONbits.TGATE = 1;
    }
    else
    {
        T4CONbits.TGATE = 0;
    }    
    
    /* PASO 6: Configurar el Pre-Scaler */
    T4CONbits.TCKPS = timer_param->prescaler & 0b00000011; 
    
    /* PASO 7: Cargar el valor TOP (PRx) */
    PR4 = timer_param->top_value;
    
    /* PASO 8: Activar el Timer de ser el caso */
    if(timer_param->timer_status == TIMER_ON)
    {
        T4CONbits.TON = 1;    
    }
    else
    {
        T4CONbits.TON = 0;
    }
  
    /* PASO 8: Activar la interrupción por comparación, de ser el caso */
    if(timer_param->match_interrupt == TIMER_INTERRUPT_ENABLED)
    {
        IEC1bits.T4IE = 1;
    }
    else
    {
        IEC1bits.T4IE = 0;
    }   
}

void Timer5_Configure(timer_c_t *timer_param)
{
     /* Inicializar el registro*/
    T5CON = 0;
    
    /* PASO 1: Desactivar el Timer */
    T5CONbits.TON = 0;

    /* PASO 2: Indicar si el Timer trabajará o no en el estado IDLE */
    if(timer_param->stop_idle == TIMER_STOP_IN_IDLE_MODE)
    {
        T5CONbits.TSIDL = 1;
    }
    else
    {
        T5CONbits.TSIDL = 0;
    }
    
    /* PASO 3: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER_EXTERNAL_CLOCK)
    {
        T5CONbits.TCS = 1;    
    }
    else
    {
        T5CONbits.TCS = 0;    
    }
    
    /* PASO 4: Configurar la acumulación de tiempo */
    if(timer_param->gated_time_accum == TIMER_GATED_TIME_ACCUMULATION_ENABLED )
    {
        T5CONbits.TGATE = 1;
    }
    else
    {
        T5CONbits.TGATE = 0;
    }    
    
    /* PASO 5: Configurar el Pre-Scaler */
    T5CONbits.TCKPS = timer_param->prescaler & 0b00000011; 
    
    /* PASO 6: Cargar el valor TOP (PRx) */
    PR5 = timer_param->top_value;
    
    /* PASO 7: Activar el Timer de ser el caso */
    if(timer_param->timer_status == TIMER_ON)
    {
        T5CONbits.TON = 1;    
    }
    else
    {
        T5CONbits.TON = 0;
    }
  
    /* PASO 8: Activar la interrupción por comparación, de ser el caso */
    if(timer_param->match_interrupt == TIMER_INTERRUPT_ENABLED)
    {
        IEC1bits.T5IE = 1;
    }
    else
    {
        IEC1bits.T5IE = 0;
    }      
}