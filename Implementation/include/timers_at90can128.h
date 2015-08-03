/*---------------------------------------------------------------------------*/
/**
 *  \file timers_at90can128.h
 *  \author Roberto Alejandro Flores Estrada
 *  \since 31/07/2015
 *
 */

#ifndef TIMERS_AT90CAN128_H_
#define TIMERS_AT90CAN128_H_

#include <cpu.h>


typedef enum
{
    eTMR0,
    eTMR1,
    eTMR2,
    eTMR3
} etmr_sel;

#define TMR0_FORCE_OUT_COMP ( 0x80 )
#define TMR0_WFG_MASK		( 0x48 )
#define TMR0_WFG_NORMAL     ( 0x00 )
#define TMR0_WFG_PHC_PWM    ( 0x01 )
#define TMR0_WFG_CTC        ( 0x02 )
#define TMR0_WFG_FPWM       ( 0x03 )

#define TMR0_COMP_MASK      ( 0x30 ) /**< Any positive change on COMP
                                           will enable OC0A pin*/
#define TMR0_COMP_NORMAL    ( 0x00 )
#define TMR0_COMP_TGL_OC0A  ( 0x01 )
#define TMR0_COMP_CLR_OC0A  ( 0x02 )
#define TMR0_COMP_SET_OC0A  ( 0x03 )

#define TMRN_CLK_SRC_MASK   ( 0x07 ) /**< For timer 0, 1 and 3 */
#define	TMRN_CLOCK_STOPPED  ( 0x00 )
#define	TMRN_NO_PRESCALER   ( 0x01 )
#define	TMRN_PRESCALER_8    ( 0x02 )
#define	TMRN_PRESCALER_64   ( 0x03 )
#define	TMRN_PRESCALER_256  ( 0x04 )
#define	TMRN_PRESCALER_1024 ( 0x05 )
#define	TMRN_EXT_NEG_EDGE   ( 0x06 )
#define	TMRN_EXT_POS_EDGE   ( 0x07 )

#define TMR0_OC0A_PORT_DIR  ( DDRB )
#define TMR0_OC0A_PIN       ( PB7  )
#define TMR0_T0_PORT_DIR    ( DDRD )
#define TMR0_T0_PIN         ( PD7  )

#define TMR0_FAST_PWM       ( ( TRUE << WGM00 ) | ( TRUE << WGM01 ) )
#define TMR0_CLR_TIME_COMP	( ( FALSE << WGM00 ) | ( TRUE << WGM01 ) )
#define TMR0_PHASE_CHG_PWM  ( ( TRUE << WGM00 ) | ( FALSE << WGM01 ) )
#define TMR0_NORMAL_MODE    ( ( FALSE << WGM00 ) | ( FALSE << WGM01 ) )
#define INPUT_OC0A( )       TMR0_OC0A_PORT_DIR = \
							( TMR0_OC0A_PORT_DIR & ~( TRUE << TMR0_OC0A_PIN ) )
#define OUTPUT_OC0A( )      TMR0_OC0A_PORT_DIR = \
                            ( TMR0_OC0A_PORT_DIR | ( TRUE << TMR0_OC0A_PIN ) )
#define INPUT_T0( )         TMR0_T0_PORT_DIR = \
							( TMR0_T0_PORT_DIR & ~( TRUE << TMR0_T0_PIN ) )
#define OUTPUT_T0( )        TMR0_T0_PORT_DIR = \
                            ( TMR0_T0_PORT_DIR | ( TRUE << TMR0_T0_PIN ) )
/*---------------------------------------------------------------------------*/

void tmr0At90can128Init( uint8_t clksrc, uint8_t wfg, uint8_t compm );
void tmr0At90can128EnableInterrupts( uint8_t val );
uint8_t tmr0At90can128GetCount( void );
void tmr0At90can128SetCount( uint8_t val );
uint8_t tmr0At90can128GetTop( void );
void tmr0At90can128SetTop( uint8_t val );
void tmr0At90can128SetupOC0A( uint8_t dir );


#endif /* TIMERS_AT90CAN128_H_ */
