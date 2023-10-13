
/* Inclusión de archivos */
#include "MT_adc.h"

/* Definición de variables */
static uint16_t *adc16_ptr = &ADCBUF0;


/* Definición de funciones */
void ADC_Configure(adc_12bit_t *adc_param)
{
    
    /* Indicar si el ADC trabajará o no en el estado IDLE */
    ADCON1bits.ADSIDL = adc_param->stop_idle & 1;
    
    /* Configurar el formato de salida de datos */
    ADCON1bits.FORM = adc_param->data_format & 0b11;
    
    /* Configurar el trigger que finalizará el muestreo e iniciará una 
     * conversión*/
    ADCON1bits.SSRC = adc_param->conversion_trigger & 0b111;
    
    /* Activar el inicio de muestreo automático, después de completar una
     * conversión, de ser el caso*/
    ADCON1bits.ASAM = adc_param->auto_sample & 1;
    
    /* Configurar el voltaje de referencia */
    ADCON2bits.VCFG = adc_param->voltage_reference & 0b111;
    
    /* Indicar si se va a escanear múltiples entradas */
    ADCON2bits.CSCNA = adc_param->scan_inputs & 1;
    
    /* Indicar cuántas conversiones deben realizarse antes de generarse 
     * una interrupción */
    ADCON2bits.SMPI = adc_param->conversions_per_interrupt & 0b1111;
    
    /* Configurar el modo del buffer (un solo buffer de 16 palabras 
     * o dos buffers de 8 palabras)*/
    ADCON2bits.BUFM = adc_param->buffer_mode & 1;
    
    /* Indicar si se desea alternar los parámetros ingresados en
     * MUXA y MUXB */
    ADCON2bits.ALTS = adc_param->input_sample_mode & 1;
            
    /* Indicar cuantos TAD debe esperarse entre el inicio del muestreo 
     * y el inicio de una conversión (auto conversión) */        
    ADCON3bits.SAMC = adc_param->auto_conversion_counter & 0b11111;  
    
    /* Configurar la fuente de señal de reloj */
    ADCON3bits.ADRC = adc_param->clock_source & 1;
    
    /* Configurar la duración de un ciclo de reloj de ADC (TAD)*/
    ADCON3bits.ADCS = adc_param->tad_value & 0b111111;
    
    /* Configurar las entradas positiva y negativa en cada multiplexor */
    ADCHSbits.CH0SA = adc_param->mux_a_pos_input & 0b1111;
    ADCHSbits.CH0NA = adc_param->mux_a_neg_input & 1;
    ADCHSbits.CH0SB = adc_param->mux_b_pos_input & 0b1111;
    ADCHSbits.CH0NB = adc_param->mux_b_neg_input & 1;
    
    /* Encender el módulo ADC, de ser el caso */
    ADCON1bits.ADON = adc_param->adc_status & 1;
    
    /* Habilitar la interrupción, de ser el caso */
    IEC0bits.ADIE = adc_param->adc_interrupt & 1;
}


void ADC_Start_Sampling(void)
{
    ADCON1bits.SAMP = 1;
}

void ADC_Finish_Sampling_Start_Conversion(void)
{
    ADCON1bits.SAMP = 0;
}

bool ADC_Read_Conversion_Flag(void)
{   
    return ADCON1bits.DONE;
}

void ADC_Clear_Conversion_Flag(void)
{
    ADCON1bits.DONE = 0;
}


void ADC_Select_Input(adc_mux_t mux, adc_pos_input_t pos, adc_neg_input_t neg)
{
    if((mux & 1) == 0)
    {
        ADCHSbits.CH0SA = pos & 0b1111;
        ADCHSbits.CH0NA = neg & 1; 
    }
    else
    {
        ADCHSbits.CH0SB = pos & 0b1111;
        ADCHSbits.CH0NB = pos & 1;  
    } 
}


void ADC_Select_Inputs_To_Scan(uint16_t adc_input_scan_mask)
{
    ADCSSL = adc_input_scan_mask;
}


uint16_t ADC_Read_Single_Converted_Value(void)
{
    return ADCBUF0;
}


void ADC_Read_Multiple_Converted_Values(uint8_t n_samples, uint16_t *buff)
{
     uint8_t counter = 0;
    
    if(n_samples < 1)
    {
        n_samples = 1;
    }
    else if(n_samples > 13)
    {
        n_samples = 13;
    }
    else
    {
        /* Sin cambio */
    }
    
    for(counter = 0; counter < n_samples; counter++)
    {
        *(buff + counter) = *(adc16_ptr + counter); 
    }   
}