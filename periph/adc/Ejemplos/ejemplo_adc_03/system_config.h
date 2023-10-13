/* 
 * File:   system_config.h
 * Author: 10421-CRIPTO01
 *
 * Created on 11 de octubre de 2023, 03:44 PM
 */

#ifndef SYSTEM_CONFIG_H
#define	SYSTEM_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif


#define FOSC    8000000UL
#define FCY     (FOSC/4)    
#include <xc.h>


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_CONFIG_H */

