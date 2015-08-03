/*---------------------------------------------------------------------------*/
/**************************************************************************//**
 *  \file      timers_at90can128.c
 * \addtogroup timers
 * @{
 *  \author    Roberto Alejandro Flores Estrada
 *  \since     31/07/2015
 *
 *****************************************************************************/

#include <timers_at90can128.h>

/**************************************************************************//**
 * \fn void tmr0At90can128Init( uint8_t clksrc, uint8_t wfg, uint8_t compm )
 *
 * \warning A prescaler reset affects all timers./n
 * 			Changing
 *****************************************************************************/
void tmr0At90can128Init( uint8_t clksrc, uint8_t wfg, uint8_t compm )
{
	clksrc &= TMRN_CLK_SRC_MASK;
	compm   =  ( compm << COM0A0 ) & TMR0_COMP_MASK;
	if ( wfg == TMR0_WFG_FPWM )
	{
		wfg = TMR0_FAST_PWM;
	}
	else if ( wfg == TMR0_WFG_CTC )
	{
		wfg = TMR0_CLR_TIME_COMP;
	}
	else if ( wfg == TMR0_WFG_PHC_PWM )
	{
		wfg = TMR0_PHASE_CHG_PWM;
	}
	else
	{
		wfg = TMR0_NORMAL_MODE;
	}
    TCCR0A  =  wfg | clksrc | compm;
}

/**************************************************************************//**
 * \fn      void tmr0At90can128EnableInterrupts( uint8_t val )
 * \param   val uint8_t Bit 0 -> TOIE0/n
 *                      Bit 1 -> OCIE0A
 * \brief   Enables/Disables Overflow and Comparator Interrupts for Timer 0
 * \warning
 * \return
 *****************************************************************************/
void tmr0At90can128EnableInterrupts( uint8_t val )
{
	TIMSK0 = val;
	return;
}

/**************************************************************************//**
 * \fn     uint8_t tmr0At90can128GetCount( void )
 * \param
 * \brief
 * \return uint8_t
 *****************************************************************************/
uint8_t tmr0At90can128GetCount( void )
{
	return TCNT0;
}

/**************************************************************************//**
 * \fn      void tmr0At90can128SetCount( uint8_t val )
 * \param   val uint8_t New count value
 * \brief   Updates the current count
 * \warning Changing it while the timer is on might cause to be triggered
 * 			immediately.
 * \return
 *****************************************************************************/
void tmr0At90can128SetCount( uint8_t val )
{
	TCNT0 = val;
	return;
}

/**************************************************************************//**
 * \fn     uint8_t tmr0At90can128GetTop( void )
 * \param
 * \brief
 * \return uint8_t
 *****************************************************************************/
uint8_t tmr0At90can128GetTop( void )
{
	return OCR0A;
}

/**************************************************************************//**
 * \fn    void tmr0At90can128SetTop( uint8_t val )
 * \param val uint8_t New Top
 * \brief
 * \return
 *****************************************************************************/
void tmr0At90can128SetTop( uint8_t val )
{
	OCR0A = val;
	return;
}

/**************************************************************************//**
 * \fn    void tmr0At90can128SetupOC0A( uint8_t dir )
 * \param
 * \brief
 * \return
 *****************************************************************************/
void tmr0At90can128SetupOC0A( uint8_t dir )
{
	if ( !dir )
	{
        INPUT_OC0A( );
	}
	else
	{
		OUTPUT_OC0A( );
	}
}

/**************************************************************************//**
 * \fn    void tmr0At90can128SetupT0( uint8_t dir )
 * \param dir uint8_t External clock pin T0 direction set
 * \brief
 * \note  T0 can be defined as output, so that the software
 *        may take control of the timer events.
 * \return
 *****************************************************************************/
void tmr0At90can128SetupT0( uint8_t dir )
{
	if ( !dir )
	{
        INPUT_T0( );
	}
	else
	{
		OUTPUT_T0( );
	}
}

/**
 * @}
 */
/*---------------------------------------------------------------------------*/
