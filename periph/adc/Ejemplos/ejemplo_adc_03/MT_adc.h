

#ifndef MT_ADC_H
#define	MT_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* Definición de tipos */    

typedef enum
{
    ADC_OFF = 0,
    ADC_ON        
}
adc_status_t;


typedef enum
{
    ADC_CONTINUE_IN_IDLE_MODE = 0,
    ADC_STOP_IN_IDLE_MODE        
}
adc_stop_idle_t;


typedef enum
{
    ADC_UNSIGNED_INT_FORMAT = 0,
    ADC_SIGNED_INT_FORMAT,
    ADC_UNSIGNED_FRACT_FORMAT,
    ADC_SIGNED_FRACT_FORMAT        
}
adc_data_output_format_t;
    

typedef enum
{
    ADC_CLEARING_SAMP_BIT_STARTS_CONVERSION = 0,
    ADC_ACTIVE_TRANSITION_INT0_STARTS_CONVERSION = 1,
    ADC_TIMER3_COMP_STARTS_CONVERSION = 2,
    ADC_MOTOR_CONTROL_PWM_INTERVAL_STARTS_CONVERSION = 3,
    ADC_INTERNAL_COUNTER_STARTS_CONVERSION = 7        
}
adc_conversion_trigger_t;


typedef enum
{
    ADC_AUTO_SAMPLE_DISABLED = 0,
    ADC_AUTO_SAMPLE_ENABLED        
}
adc_auto_sample_t;


typedef enum
{
    ADC_VREF_VDD = 0,
    ADC_VREF_EXTERNAL = 3        
}
adc_voltage_reference_t;
    

typedef enum
{
    ADC_SCAN_INPUTS_DISABLED = 0,
    ADC_SCAN_INPUTS_ENABLED        
}
adc_scan_inputs_t;


typedef enum
{
    ADC_01_CONV_PER_INT = 0,
    ADC_02_CONV_PER_INT,
    ADC_03_CONV_PER_INT,
    ADC_04_CONV_PER_INT,
    ADC_05_CONV_PER_INT,
    ADC_06_CONV_PER_INT,
    ADC_07_CONV_PER_INT,
    ADC_08_CONV_PER_INT,
    ADC_09_CONV_PER_INT,  
    ADC_10_CONV_PER_INT,
    ADC_11_CONV_PER_INT,
    ADC_12_CONV_PER_INT,
    ADC_13_CONV_PER_INT              
}
adc_conversions_per_interrupt_t;


typedef enum
{
    ADC_BUFFER_1_X_16WORD = 0,
    ADC_BUFFER_2_X_8WORD        
}
adc_buffer_mode_t;


typedef enum
{
    ADC_USE_ALWAYS_MUXA = 0,
    ADC_ALTERNATE_MUXA_MUXB        
}
adc_alternate_input_sample_mode_t;


typedef enum
{
    ADC_AUTO_CONV_COUNTER_00_TAD = 0,
    ADC_AUTO_CONV_COUNTER_01_TAD,
    ADC_AUTO_CONV_COUNTER_02_TAD,
    ADC_AUTO_CONV_COUNTER_03_TAD,
    ADC_AUTO_CONV_COUNTER_04_TAD,
    ADC_AUTO_CONV_COUNTER_05_TAD,
    ADC_AUTO_CONV_COUNTER_06_TAD,
    ADC_AUTO_CONV_COUNTER_07_TAD,
    ADC_AUTO_CONV_COUNTER_08_TAD,
    ADC_AUTO_CONV_COUNTER_09_TAD,
    ADC_AUTO_CONV_COUNTER_10_TAD,
    ADC_AUTO_CONV_COUNTER_11_TAD,
    ADC_AUTO_CONV_COUNTER_12_TAD,
    ADC_AUTO_CONV_COUNTER_13_TAD,
    ADC_AUTO_CONV_COUNTER_14_TAD,
    ADC_AUTO_CONV_COUNTER_15_TAD,
    ADC_AUTO_CONV_COUNTER_16_TAD,
    ADC_AUTO_CONV_COUNTER_17_TAD,
    ADC_AUTO_CONV_COUNTER_18_TAD,
    ADC_AUTO_CONV_COUNTER_19_TAD,
    ADC_AUTO_CONV_COUNTER_20_TAD,
    ADC_AUTO_CONV_COUNTER_21_TAD,
    ADC_AUTO_CONV_COUNTER_22_TAD,
    ADC_AUTO_CONV_COUNTER_23_TAD,
    ADC_AUTO_CONV_COUNTER_24_TAD,
    ADC_AUTO_CONV_COUNTER_25_TAD,
    ADC_AUTO_CONV_COUNTER_26_TAD,
    ADC_AUTO_CONV_COUNTER_27_TAD,
    ADC_AUTO_CONV_COUNTER_28_TAD,
    ADC_AUTO_CONV_COUNTER_29_TAD,
    ADC_AUTO_CONV_COUNTER_30_TAD,            
    ADC_AUTO_CONV_COUNTER_31_TAD 
}
adc_auto_conversion_counter_limit_t;


typedef enum
{
    ADC_CLOCK_DERIVED_FROM_FCY = 0,
    ADC_INTERNAL_RC_CLOCK        
}
adc_clock_source_t;


typedef enum
{
    ADC_TAD_TCY_2 = 0,
    ADC_TAD_TCY,
    ADC_TAD_3TCY_2,
    ADC_TAD_2TCY,
    ADC_TAD_5TCY_2,
    ADC_TAD_3TCY,
    ADC_TAD_7TCY_2,        
    ADC_TAD_4TCY,
    ADC_TAD_9TCY_2,        
    ADC_TAD_5TCY,
    ADC_TAD_11TCY_2,        
    ADC_TAD_6TCY,
    ADC_TAD_13TCY_2,        
    ADC_TAD_7CY,
    ADC_TAD_15TCY_2,        
    ADC_TAD_8TCY,
    ADC_TAD_17TCY_2,        
    ADC_TAD_9TCY,
    ADC_TAD_19TCY_2,        
    ADC_TAD_10TCY,
    ADC_TAD_21TCY_2,         
    ADC_TAD_11TCY,
    ADC_TAD_23TCY_2,          
    ADC_TAD_12TCY,
    ADC_TAD_25TCY_2,          
    ADC_TAD_13TCY,
    ADC_TAD_27TCY_2,          
    ADC_TAD_14TCY,
    ADC_TAD_29TCY_2,          
    ADC_TAD_15TCY,
    ADC_TAD_31TCY_2,          
    ADC_TAD_16TCY,
    ADC_TAD_33TCY_2,          
    ADC_TAD_17CY,
    ADC_TAD_35TCY_2,          
    ADC_TAD_18TCY,
    ADC_TAD_37TCY_2,          
    ADC_TAD_19TCY,
    ADC_TAD_39TCY_2,          
    ADC_TAD_20TCY,
    ADC_TAD_41TCY_2,          
    ADC_TAD_21TCY,
    ADC_TAD_43TCY_2,          
    ADC_TAD_22TCY,
    ADC_TAD_45TCY_2,          
    ADC_TAD_23TCY,
    ADC_TAD_47TCY_2,          
    ADC_TAD_24TCY,
    ADC_TAD_49TCY_2,          
    ADC_TAD_25TCY,
    ADC_TAD_51TCY_2,          
    ADC_TAD_26TCY,
    ADC_TAD_53TCY_2,          
    ADC_TAD_27TCY,
    ADC_TAD_55TCY_2,          
    ADC_TAD_28TCY,
    ADC_TAD_57TCY_2,          
    ADC_TAD_29TCY,
    ADC_TAD_59TCY_2,          
    ADC_TAD_30TCY,
    ADC_TAD_61TCY_2,          
    ADC_TAD_31TCY,
    ADC_TAD_63TCY_2,          
    ADC_TAD_32TCY        
}
adc_conversion_clock_t;


typedef enum
{
    ADC_POS_INPUT_AN0 = 0,
    ADC_POS_INPUT_AN1,
    ADC_POS_INPUT_AN2,
    ADC_POS_INPUT_AN3,
    ADC_POS_INPUT_AN4,      
    ADC_POS_INPUT_AN5,
    ADC_POS_INPUT_AN6,
    ADC_POS_INPUT_AN7,
    ADC_POS_INPUT_AN8,
    ADC_POS_INPUT_AN9,
    ADC_POS_INPUT_AN10,
    ADC_POS_INPUT_AN11,
    ADC_POS_INPUT_AN12              
}
adc_pos_input_t;


typedef enum
{
    ADC_NEG_INPUT_VREF_NEG = 0,
    ADC_NEG_INPUT_AN1        
}
adc_neg_input_t;


typedef enum
{
    ADC_MUXA = 0,
    ADC_MUXB        
}
adc_mux_t;


typedef enum
{
    ADC_INTERRUPT_DISABLED = 0,
    ADC_INTERRUPT_ENABLED        
}
adc_interrupt_status_t;


typedef struct
{
    //Estos parámetros son los principales
    adc_status_t adc_status;
    adc_data_output_format_t data_format;
    adc_stop_idle_t stop_idle;
    adc_conversion_trigger_t conversion_trigger;
    adc_auto_sample_t auto_sample;
    adc_voltage_reference_t voltage_reference;
    adc_auto_conversion_counter_limit_t auto_conversion_counter;
    adc_clock_source_t clock_source;
    adc_conversion_clock_t  tad_value;
    adc_pos_input_t mux_a_pos_input;
    adc_neg_input_t mux_a_neg_input;
    adc_pos_input_t mux_b_pos_input;
    adc_neg_input_t mux_b_neg_input;
    adc_interrupt_status_t adc_interrupt;
    
    // Estos parámetros son relevantes cuando se leen múltiples entradas
    adc_conversions_per_interrupt_t conversions_per_interrupt;
    adc_scan_inputs_t scan_inputs;
    adc_buffer_mode_t buffer_mode;
    adc_alternate_input_sample_mode_t input_sample_mode;
}
adc_12bit_t;

/* Declaración de funciones */
void ADC_Configure(adc_12bit_t *adc_param);
void ADC_Start_Sampling(void);
void ADC_Finish_Sampling_Start_Conversion(void);
bool ADC_Read_Conversion_Flag(void);
void ADC_Clear_Conversion_Flag(void);
void ADC_Select_Input(adc_mux_t mux, adc_pos_input_t pos, adc_neg_input_t neg);
void ADC_Select_Inputs_To_Scan(uint16_t adc_input_scan_mask);
uint16_t ADC_Read_Single_Converted_Value(void);
void ADC_Read_Multiple_Converted_Values(uint8_t n_samples, uint16_t *buff);


#ifdef	__cplusplus
}
#endif

#endif	/* MT_ADC_H */

