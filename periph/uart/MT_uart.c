/* Inclusión de archivos */
#include "MT_uart.h"

/* Definición de funciones */
void UART1_Configure(uart_t *uart_param)
{

    uint32_t my_spbrg = 0;
    
    /* Limpiar los registros */
    U1MODE = 0;
    U1STA = 0;
    
    /* Habilitar el módulo UART */
    U1MODEbits.UARTEN = 1;

    /* Configurar el baudrate deseado */
    my_spbrg = ((FCY / uart_param->baud_rate) / 16) - 1;
    U1BRG = my_spbrg;
        
    /* Habilitar/deshabilitar la transmisión */
    if(uart_param->tx_status == UART_TX_ENABLED)
    {
        U1STAbits.UTXEN = 1;
    }
    else
    {
        U1STAbits.UTXEN = 0;
    }
    
    /* Configurar el número de bits de datos */
    if(uart_param->data_bits == UART_9_DATA_BITS)
    {
        U1MODEbits.PDSEL = 0b00000011;
    }
    else
    {
        /* Configurar el bit de paridad */
        if(uart_param->parity_mode == UART_PARITY_EVEN)
        {
            U1MODEbits.PDSEL = 0b00000001;
        }
        else if(uart_param->parity_mode == UART_PARITY_ODD)
        {
            U1MODEbits.PDSEL = 0b00000010;
        }
        else
        {
            U1MODEbits.PDSEL = 0b00000000;
        }
    }
    
    /* Configurar el número de bits de parada */
    if(uart_param->stop_bits == UART_2_STOP_BITS)
    {
        U1MODEbits.STSEL = 1;      
    }
    else
    {
        U1MODEbits.STSEL = 0;    
    }    
    
      
    /* Habilitar/deshabilitar la interrupción por recepción serial completada */
    if(uart_param->rx_interrupt == UART_RX_INTERRUPT_ENABLED)
    {
        U1STAbits.URXISEL = 0;
        IEC0bits.U1RXIE = 1;
    }
    else
    {
        IEC0bits.U1RXIE = 0;
    }
  
    /* Habilitar/deshabilitar la interrupción por transmisión serial completada */
    if(uart_param->tx_interrupt == UART_TX_INTERRUPT_ENABLED)
    {
        U1STAbits.UTXISEL = 0;
        IEC0bits.U1TXIE = 1;
    }
    else
    {
       IEC0bits.U1TXIE = 0;
    }   
    
}


void UART2_Configure(uart_t *uart_param)
{

    uint32_t my_spbrg = 0;
    
    /* Limpiar los registros */
    U2MODE = 0;
    U2STA = 0;
    
    /* Habilitar el módulo UART */
    U2MODEbits.UARTEN = 1;

    /* Configurar el baudrate deseado */
    my_spbrg = ((FCY / uart_param->baud_rate) / 16) - 1;
    U2BRG = my_spbrg;
        
    /* Habilitar/deshabilitar la transmisión */
    if(uart_param->tx_status == UART_TX_ENABLED)
    {
        U2STAbits.UTXEN = 1;
    }
    else
    {
        U2STAbits.UTXEN = 0;
    }
    
    /* Configurar el número de bits de datos */
    if(uart_param->data_bits == UART_9_DATA_BITS)
    {
        U2MODEbits.PDSEL = 0b00000011;
    }
    else
    {
        /* Configurar el bit de paridad */
        if(uart_param->parity_mode == UART_PARITY_EVEN)
        {
            U2MODEbits.PDSEL = 0b00000001;
        }
        else if(uart_param->parity_mode == UART_PARITY_ODD)
        {
            U2MODEbits.PDSEL = 0b00000010;
        }
        else
        {
            U2MODEbits.PDSEL = 0b00000000;
        }
    }
    
    /* Configurar el número de bits de parada */
    if(uart_param->stop_bits == UART_2_STOP_BITS)
    {
        U2MODEbits.STSEL = 1;      
    }
    else
    {
        U2MODEbits.STSEL = 0;    
    }    
    
      
    /* Habilitar/deshabilitar la interrupción por recepción serial completada */
    if(uart_param->rx_interrupt == UART_RX_INTERRUPT_ENABLED)
    {
        U2STAbits.URXISEL = 0;
        IEC1bits.U2RXIE = 1;
    }
    else
    {
        IEC1bits.U2RXIE = 0;
    }
  
    /* Habilitar/deshabilitar la interrupción por transmisión serial completada */
    if(uart_param->tx_interrupt == UART_TX_INTERRUPT_ENABLED)
    {
        U2STAbits.UTXISEL = 0;
        IEC1bits.U2TXIE = 1;
    }
    else
    {
       IEC1bits.U2TXIE = 0;
    }   
    
}




void UARTn_Tx_Byte(uart_module_t uart_n, char byte)
{
    
    switch(uart_n)
    {
        case UART1_MOD:
            while(U1STAbits.TRMT == 0){
                /* Esperar hasta que la transmisión anterior se haya completado */
            }
            /* Cargar el dato al registro TXREG */
            U1TXREG = byte;            
            break;
            
        case UART2_MOD:
            while(U2STAbits.TRMT == 0){
                /* Esperar hasta que la transmisión anterior se haya completado */
            }
            /* Cargar el dato al registro TXREG */
            U2TXREG = byte;            
            break;            
            
        default:
            break;
    }    
  
}


void UARTn_Tx_String(uart_module_t uart_n, char str[])
{
    
    uint8_t indice = 0;
    
    /* Transmitir hasta encontrar el caracter nulo */
    while(str[indice] != '\0'){
        UARTn_Tx_Byte(uart_n, str[indice]);
        indice++;
    }
    
}


void UARTn_Tx_Integer(uart_module_t uart_n, int32_t num)
{

	char signo_y_digitos[12];
	uint8_t signo = 0;
	int32_t digito;
	int8_t indice = 11;

	/* Determinar el signo del número */
	if(num < 0){
		signo = 1;
		num = -num;
	}

	/* Indicar el fin de la cadena de caracteres */
	signo_y_digitos[indice--] = '\0';

	/* Extraer los dígitos uno a uno, empezando por las unidades */
	do{
		digito = (num % 10) + '0';
		signo_y_digitos[indice--] = (char)digito;
		num /= 10;
	}while(num != 0);

	/* Agregar el signo (de ser necesario) */
	if(signo){
		signo_y_digitos[indice] = '-';
	}else{
		indice++;
	}

	/* Transmitir el número */
	UARTn_Tx_String(uart_n, &signo_y_digitos[indice]);
}