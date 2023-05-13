

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_uart.h"
#include "MT_timer.h"

/* Declaración de macros */
void UART1_Initialize(void);
void Timer1_Initialize(void);

/* Función principal */
int main(void)
{    
    /* Configurar el UART1: 9600 bps, 8bits de datos, 1 bit de parada y sin paridad */
    UART1_Initialize();
    /* Configurar el Timer1 para contar 500 ms */
    
    while(1)
    {
        /* Imprimir mensaje cada 500 ms*/
        if(IFS0bits.T1IF == 1)
        {
           IFS0bits.T1IF = 0;
           UARTn_Tx_String(UART1_MOD, "Hola.\n\r");
        }   
    }
    
    return 0;
}


/* Definición de funciones */

void UART1_Initialize(void)
{

    uart_t my_uart;

    my_uart.baud_rate = 9600;
    my_uart.data_bits = UART_8_DATA_BITS;
    my_uart.parity_mode = UART_PARITY_DISABLED;
    my_uart.stop_bits = UART_1_STOP_BIT;
    my_uart.rx_interrupt = UART_RX_INTERRUPT_DISABLED;
    my_uart.tx_interrupt = UART_TX_INTERRUPT_DISABLED;
    my_uart.tx_status = UART_TX_ENABLED;
    
    UART1_Configure(&my_uart);
}

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