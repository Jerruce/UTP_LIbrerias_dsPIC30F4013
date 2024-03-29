
/* Inclusi�n de archivos */
#include "system_config.h"
#include <libpic30.h>
#include "MT_adc.h"

/* Definici�n de macros */    
#define POTENTIOMETER       0

/* Declaraci�n de funciones */
void ADC_Initialize(void);

/* Funci�n principal */
int main(void) {
    
    uint16_t adc_value = 0;
    
    /* Configurar los pines de los LEDs (RB13 - RB1) como salida */
    TRISB = 0x0001;
    /* Solamente el pin RB0 ser� entrada anal�gica */
    ADPCFG = ~(1 << POTENTIOMETER);
    /* Configurar el m�dulo ADC para conversi�n en MODO MANUAL */
    ADC_Initialize();
    /* Seleccionar el la entrada que se desea leer con el ADC (AN0) 
     * NOTA: El �ltimo par�metro siempre es ADC_NEG_INPUT_VREF_NEG */
    ADC_Select_Input(ADC_MUXA, ADC_POS_INPUT_AN0, ADC_NEG_INPUT_VREF_NEG);
    
    while(1)
    {
        /* Iniciar el muestreo, la conversi�n iniciar� de forma autom�tica
         * luego de que transcurra 1TAD (valor indicado al contador interno) */
        ADC_Start_Sampling();
        /* Esperar a que la conversi�n se complete */
        while(ADC_Read_Conversion_Flag() == 0)
        {
            /* Esperando ...*/
        }
        /* Leer el valor ADC */
        adc_value = ADC_Read_Single_Converted_Value();
        /* Mostrar el valor ADC por los LEDs del PUERTO B */
        LATB = (adc_value << 1);
        
        /* Esperar 10 ms antes de repetir el ciclo */
        __delay_ms(10);
    }
    
    return 0;
}


/* Definici�n de funciones */

void ADC_Initialize(void)
{
    adc_12bit_t my_adc;
    
     //Estos par�metros son los principales
    
    my_adc.stop_idle = ADC_CONTINUE_IN_IDLE_MODE; // Valor por defecto
    my_adc.adc_status = ADC_ON; // Encender ADC
    my_adc.voltage_reference = ADC_VREF_VDD; // Usar VDD (5V) como referencia
    my_adc.data_format = ADC_UNSIGNED_INT_FORMAT; // Formato entero sin signo
    my_adc.clock_source = ADC_CLOCK_DERIVED_FROM_FCY; // Usar el reloj del CPU
    my_adc.tad_value = ADC_TAD_2TCY; // 1TAD = 2 * TCY = 2 * 500ns = 1us    (TAD m�nimo: 667 ns)
    my_adc.auto_sample = ADC_AUTO_SAMPLE_DISABLED; // Desactivar el muestreo autom�tico
    my_adc.conversion_trigger = ADC_INTERNAL_COUNTER_STARTS_CONVERSION; // Conversi�n activada por contador interno
    my_adc.auto_conversion_counter = ADC_AUTO_CONV_COUNTER_01_TAD; // Contador de auto-conversi�n
    my_adc.mux_a_pos_input = ADC_POS_INPUT_AN0; // Entrada positiva MUXA
    my_adc.mux_a_neg_input = ADC_NEG_INPUT_VREF_NEG; //Entrada negativa MUXA
    my_adc.mux_b_pos_input = ADC_POS_INPUT_AN0; // Entrada positiva MUXB
    my_adc.mux_b_neg_input = ADC_NEG_INPUT_VREF_NEG; //Entrada negativa MUXB
    my_adc.input_sample_mode = ADC_USE_ALWAYS_MUXA; // Usar siempre la configuraci�n del MUXA    
    my_adc.adc_interrupt = ADC_INTERRUPT_DISABLED; // Interrupci�n deshabilitada
    
    
    // Estos par�metros son m�s relevantes cuando se leen m�ltiples entradas
    
    my_adc.conversions_per_interrupt = ADC_01_CONV_PER_INT; // Una conversi�n por interrupci�n
    my_adc.scan_inputs = ADC_SCAN_INPUTS_DISABLED; // Escaneo de m�ltiples canales deshabilitado
    my_adc.buffer_mode = ADC_BUFFER_1_X_16WORD; // Un solo buffer de 16 valores

    ADC_Configure(&my_adc); 
}