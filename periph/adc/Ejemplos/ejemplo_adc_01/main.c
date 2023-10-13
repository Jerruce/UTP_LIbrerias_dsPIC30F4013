/* Inclusión de archivos */
#include "system_config.h"
#include <libpic30.h>
#include "MT_adc.h"

/* Definición de macros */
  
#define POTENTIOMETER       0
#define LED                 1

/* Declaración de funciones */
void ADC_Initialize(void);

/* Función principal */
int main(void) {
    
    uint16_t adc_value = 0;
    
    /* Configurar el pin del LED (RB1) como salida */
    TRISB = ~(1 << LED);
    /* Solamente el pin RB0 será entrada analógica */
    ADPCFG = ~(1 << POTENTIOMETER);
    /* Configurar el módulo ADC para conversión en MODO MANUAL */
    ADC_Initialize();
    /* Seleccionar el la entrada que se desea leer con el ADC (AN0) 
     * NOTA: El último parámetro siempre es ADC_NEG_INPUT_VREF_NEG */
    ADC_Select_Input(ADC_MUXA, ADC_POS_INPUT_AN0, ADC_NEG_INPUT_VREF_NEG);
    
    while(1)
    {
        /* Iniciar un muestreo */
        ADC_Start_Sampling();
        /* Esperar un microsegundo a que se complete el muestreo */
        __delay_us(1);
        /* Detener el muestreo e iniciar la conversión*/
        ADC_Finish_Sampling_Start_Conversion();
        /* Esperar a que la conversión se complete */
        while(ADC_Read_Conversion_Flag() == 0)
        {
            /* Esperando ...*/
        }
        /* Leer el valor ADC */
        adc_value = ADC_Read_Single_Converted_Value();
        /* Si el potenciómetro superó su valor central (2048) ... */
        if(adc_value > 2048)
        {
            /* Encender el LED */
            LATBbits.LATB1 = 1; // Forma 1
            //LATB |= (1 << LED); // Forma 2
        }
        else /* De lo contrario ... */
        {
            /* Apagar el LED */
            LATBbits.LATB1 = 0;    // Forma 1
            //LATB &= ~(1 << LED); // Forma 2
        }
        
        /* Esperar 10 ms antes de repetir el ciclo */
        __delay_ms(10);
    }
    
    return 0;
}

/* Deinición de funciones */

void ADC_Initialize(void)
{
    adc_12bit_t my_adc;
    
     //Estos parámetros son los principales
    
    my_adc.stop_idle = ADC_CONTINUE_IN_IDLE_MODE; // Valor por defecto
    my_adc.adc_status = ADC_ON; // Encender ADC
    my_adc.voltage_reference = ADC_VREF_VDD; // Usar VDD (5V) como referencia
    my_adc.data_format = ADC_UNSIGNED_INT_FORMAT; // Formato entero sin signo
    my_adc.clock_source = ADC_CLOCK_DERIVED_FROM_FCY; // Usar el reloj del CPU
    my_adc.tad_value = ADC_TAD_2TCY; // 1TAD = 2 * TCY = 2 * 500ns = 1us    (TAD mínimo: 667 ns)
    my_adc.auto_sample = ADC_AUTO_SAMPLE_DISABLED; // Desactivar el muestreo automático
    my_adc.conversion_trigger = ADC_CLEARING_SAMP_BIT_STARTS_CONVERSION; // Conversión en MODO MANUAL
    my_adc.auto_conversion_counter = ADC_AUTO_CONV_COUNTER_01_TAD; // Contador de auto-conversión
    my_adc.mux_a_pos_input = ADC_POS_INPUT_AN0; // Entrada positiva MUXA
    my_adc.mux_a_neg_input = ADC_NEG_INPUT_VREF_NEG; //Entrada negativa MUXA
    my_adc.mux_b_pos_input = ADC_POS_INPUT_AN0; // Entrada positiva MUXB
    my_adc.mux_b_neg_input = ADC_NEG_INPUT_VREF_NEG; //Entrada negativa MUXB
    my_adc.input_sample_mode = ADC_USE_ALWAYS_MUXA; // Usar siempre la configuración del MUXA    
    my_adc.adc_interrupt = ADC_INTERRUPT_DISABLED; // Interrupción deshabilitada
    
    
    // Estos parámetros son más relevantes cuando se leen múltiples entradas
    
    my_adc.conversions_per_interrupt = ADC_01_CONV_PER_INT; // Una conversión por interrupción
    my_adc.scan_inputs = ADC_SCAN_INPUTS_DISABLED; // Escaneo de múltiples canales deshabilitado
    my_adc.buffer_mode = ADC_BUFFER_1_X_16WORD; // Un solo buffer de 16 valores

    ADC_Configure(&my_adc); 
}