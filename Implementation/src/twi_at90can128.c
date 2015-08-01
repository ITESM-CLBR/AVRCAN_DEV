/*---------------------------------------------------------------------------*/
/**************************************************************************//**
 * \file       twi_at90can128.c
 * \addtogroup two_wire_interface
 * @{
 * \since      13/07/2015
 * \version    0.1
 * \author     Roberto Alejandro Flores Estrada
 *****************************************************************************/
#include <twi_at90can128.h>


static uint8_t  twiSla = 0;                        /**< Slave Address */
static uint8_t  *twiTxDataBuffer = NULL;           /**< Pointer to the current
                                                        data recipient or
                                                        source. */
static uint8_t  twiRxDataBuffer[ MAX_TW_RX_DATA ]; /**< Slave mode data
                                                        buffer */
static uint32_t twiTxDataLen = 0;                  /**< Data buffer length. */
static uint32_t twiTxDataIdx = 0;                  /**< Allows moving through
                                                        the data buffer */
static uint32_t twiRxDataLen = 0;                  /**< Data buffer length. */
static uint32_t twiRxDataIdx = 0;                  /**< Slave mode data
                                                        index */
static uint8_t twiInProgress = 0;                  /**< Indicates the data
                                                        received is valid */
/*---------------------------------------------------------------------------*/

/**************************************************************************//**
 *  \fn      void TWI_at90can128_Init( uint8_t gCallEnable, uint8_t address,
                          uint8_t baudrate, uint8_t prescaler  )
 *  \param   GCallEnable uint8_t Enables support for general call
 *  \param   address    uint8_t slave mode address
 *  \param   baudrate   uint8_t transfer bit rate
 *  \param   prescaler  uint8_t Determines the interface frequency.
 *  \brief   Setups the two-wire interface peripheral.
 *  \warning Address is aligned to TWAR, LSB is TWGE but it will be discarded,
 *           and that bit will be set/cleared in TWAR by gCallEnable instead.
 *  \return  none
 *****************************************************************************/
void TWI_at90can128_Init( uint8_t gCallEnable, uint8_t address,
                          uint8_t baudrate, uint8_t prescaler )
{
    twcrBf tbf;

    tbf.byte = TWCR_DEFAULT;

    twiInProgress = FALSE;//No active operation.
    TWSR = prescaler;     //Status bits are read only. Setting the
                          //prescaler.
    TWBR = baudrate;      //Setting the baudrate.
    if ( address )        //Address must be unique and non-zero.
    {                     //Zero is used for broadcasting.
        TWAR = address;

    }
    else
    {
        TWAR = TWIADDR;    //Default address as it can't be 0x00.
    }
    if ( gCallEnable )
    {
        TWAR = TWAR | TW_GLOBAL_CALL_ON;
    }
    else
    {
        TWAR = TWAR & ~TW_GLOBAL_CALL_ON;
    }
    tbf.bits.btwen = TW_BIT_ON;  //Enabling the TW interface
    tbf.bits.btwea = TW_BIT_ON;  //Starts on Slave mode. Allows
                                 //acknowledging the address or
                                 //general call ( if enabled ).
    twiRxDataIdx = 0;
    TWCR = tbf.byte;             //Updating the Two wire control register.

    return;
}

/**************************************************************************//**
 *  \fn     void TWI_at90can128_enableInterrupt( uint8_t btwie )
 *  \param  btwie uint8_t If ON enables interrupt, else turns it off
 *  \brief  Changes the value of TWIE from TWCR
 *  \note   Global interruption (SREG) must be enabled as well.
 *  \return none
 *****************************************************************************/
void TWI_at90can128_enableInterrupt( uint8_t btwie )
{
    twcrBf tbf;

    tbf.byte = TWCR;
    tbf.bits.btwie = btwie;      //Enable/Disable interruption
    tbf.bits.btwint = TW_BIT_ON; //Releases any stuck process.
    TWCR = tbf.byte;

    return;
}

/**************************************************************************//**
 *  \fn      uint8_t TWI_at90can128_sendMsg( uint8_t address, uint8_t *data,
                                 uint32_t* length, uint8_t opt )
 *  \param   address  uint8_t   Destination address
 *  \param   data     uint8_t*  Data buffer
 *  \param   length   uint32_t* Data buffer length
 *  \param   opt      uint8_t   If TRUE -> a Read operation,
 *                              If FALSE-> a Write operation
 *  \brief   Sends an address, a Read/Write request and reads or writes n
 *           bytes from/to the bus.
 *  \note    Address may be zero for broadcasting. Sending address 0x00
 *           requesting a read will not proceed, due collision within
 *           the slaves in the bus.
 *  \warning This function assumes 7 bit addresses, where its least
 *           significant bit is the Read/Write bit. This bit is set or
 *           cleared depending on opt argument.
 *  \return  uint8_t Boolean value
 *****************************************************************************/
uint8_t TWI_at90can128_sendMsg( uint8_t address, uint8_t *data,
                                 uint32_t* length, uint8_t opt )
{
    twcrBf tbf;
    uint8_t ret = FALSE;

    if ( ( length ) && ( data ) )
    {
        twiInProgress   = TRUE;
        tbf.byte = TWCR;
        tbf.bits.btwen  = TW_BIT_ON;  // Enables TW interface
        tbf.bits.btwint = TW_BIT_ON;  // Clears the interrupt flag
        tbf.bits.btwsta = TW_BIT_ON;  // Triggers start condition.
        if ( opt ) // READ
        {
            twiSla = ( address | TW_READ );
        }
        else       // WRITE
        {
            twiSla = ( uint32_t )( address & ~TW_READ );
        }
        twiTxDataBuffer  = data;
        twiTxDataLen     = *length;
        TWCR = tbf.byte;
        ret  = TRUE; // Success
    }

    return ret;
}

/**************************************************************************//**
 *  \fn uint8_t TWI_at90can128_getData( void )
 *  \param  none
 *  \brief  Read received data in master mode.
 *  \return none
 *****************************************************************************/
uint8_t* TWI_at90can128_getData( void )
{
    return twiTxDataBuffer;
}

/**************************************************************************//**
 * \fn uint8_t TWI_at90can128_isBusy( void )
 * \param none
 * \brief Returns true if there is a pending operation in Master mode.
 * \return uint8_t Boolean value
 *****************************************************************************/
uint8_t TWI_at90can128_isBusy( void )
{
    return twiInProgress;
}

/**************************************************************************//**
 *  \fn     uint8_t TWI_at90can128_evaluateStep( void )
 *  \param  none
 *  \brief  Decodes the current status to determine what to
 *          write into the Control register.
 *  \return uint8_t Returns the two wire interface current status
 *****************************************************************************/
uint8_t TWI_at90can128_evaluateStep( void )
{
    twcrBf tbf;
    uint8_t ret = TW_STATUS;

    tbf.byte = TWCR;
    /**
     * \par Behavior\n\n
     */
    switch ( ret )
    {

    /** - START and REPEATED START states\n
    *    These states are reached when the start condition was
    *    transmitted successfully, therefore becoming the Master of
    *    the bus.\n
    *      - If TWINT is set, the start condition won't be sent,
    *        therefore it should be cleared first by writing a
    *        one over it, before sending the start condition.\n
    *      - In master mode sending a repeated start will not relinquish
    *        the master control over the bus, unless it lost arbitration.\n
    *      - By writing a one at TWSTA bit in TWCR the MCU unit tries to
    *        acquire control over the bus as the master.\n
    *      - TWSTA must be clearing in software after sending it.\n
    */
    case TW_START:                    // 0x08
    case TW_REP_START:                // 0x10
        twiTxDataIdx = 0;
        TWDR = twiSla;                // Sending Slave Address. TWDR is
                                      // bidirectional.
        tbf.bits.btwen  = TW_BIT_ON;  // Make sure the Interface is on.
        tbf.bits.btwsta = TW_BIT_OFF; // Start already sent, must be
                                      // cleared in software.
        tbf.bits.btwsto = TW_BIT_OFF;
        tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
        twiInProgress   = TRUE;
        break;

    /** - Master Transmitted Address/Data + ACK\n
     *    These states are active after successfully byte and
     *    received an ACK.\n
     *     - After the last byte have been sent, the stop bit condition
     *       must be set by software.\n
     *     - Interruption flag TWINT must be cleared by writing a one,
     *       otherwise it will not proceed to the next state.\n
     *     - STOP bit condition TWSTO is cleared automatically.\n
     */
    case TW_MT_SLA_ACK:               // 0x18
    case TW_MT_DATA_ACK:              // 0x28
        if ( twiTxDataIdx < twiTxDataLen )
        {
            // Writing TWDR must be done while TWINT is high, if the TWDR
            // is written when TWINT is low the TWWC bit in TWCR will be
            // be set and the operation will be cancelled.
            TWDR = ( twiTxDataBuffer )[ twiTxDataIdx++ ];
            tbf.bits.btwen  = TW_BIT_ON;  // Make sure the Interface is on.
            tbf.bits.btwsta = TW_BIT_OFF;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
            twiInProgress   = TRUE;
        }
        else // All data is already sent, complete the frame by sending the
             // stop condition.
        {
            twiInProgress   = FALSE;
            tbf.bits.btwen  = TW_BIT_ON;  // Make sure the Interface is on.
            tbf.bits.btwsta = TW_BIT_OFF;
            tbf.bits.btwsto = TW_BIT_ON;  // Stop condition send.
            tbf.bits.btwea  = TW_BIT_ON;  // Allows address recognition.
            tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
            twiInProgress   = FALSE;
        }
        break;
    /** - Master Transmitting Data, Received NACK\n
     *    It may happen because the slave can't handle any more data,
     *    then continue sending the same data won't result on any change.\n
     *    - Cancel the current operation by sending STOP condition.\n
     *    - Returns to slave mode.\n
     */
    case TW_MT_DATA_NACK:             // 0x30
        tbf.bits.btwen = TW_BIT_ON;   // Make sure the Interface is on.
        tbf.bits.btwsta = TW_BIT_OFF;
        tbf.bits.btwsto = TW_BIT_ON;  // Stop condition send.
        tbf.bits.btwea  = TW_BIT_ON;  // Allows address recognition.
        tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
        twiInProgress   = FALSE;
        break;

    /** - Master Transmitted Slave Address and Received Acknowledge
     *    (Read operation)\n
     *    When sending SLA+R and as a result the slave replied with an ACK,
     *    this state is reached.\n
     *    - No action other than clearing TWINT is done, data will be read
     *      at the next interruption.\n
     */
    case TW_MR_SLA_ACK:               // 0x40
         tbf.bits.btwen  = TW_BIT_ON;
         tbf.bits.btwsta = TW_BIT_OFF;
         tbf.bits.btwsto = TW_BIT_OFF;
         tbf.bits.btwint = TW_BIT_ON; // Must be cleared to proceed.
         twiInProgress   = TRUE;
         break;
    /** - Master Received data from Slave and is about to transmit ACK\n
     *    After SLA+R the slave will start sending data while the master
     *    continues replying with an ACK. The last byte will be followed
     *    by a NACK.\n
     */
    case TW_MR_DATA_ACK:              // 0x50
        if ( twiTxDataIdx < ( twiTxDataLen - 1 ) )
        {
            ( twiTxDataBuffer )[ twiTxDataIdx++ ] = TWDR;
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsta = TW_BIT_OFF;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_ON;  // Master sends an ACK.
            tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
            twiInProgress   = TRUE;
        }
        else if ( twiTxDataIdx < twiTxDataLen )
        {
            ( twiTxDataBuffer )[ twiTxDataIdx++ ] = TWDR;
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsta = TW_BIT_OFF;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_OFF; // Master sends an NACK.
            tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
            twiInProgress   = TRUE;
        }
        else
        {
            /*TODO We must prevent from filling the data buffer.
                   It was expected that the previous byte was
                   the last one and thereby the NACK was sent, but the
                   slave might missed it.
            */
        }
        break;
    /** - Slave transmit\n
     *
     */
    case TW_ST_LAST_DATA:             // 0xC8
         /* No break */
    /** - Master Receiving data, transmitted a NACK
     *    When the last byte was received and the Master replied a NACK,
     *    the master should end the communication.
     *
     */
    case TW_MR_DATA_NACK:             // 0x58
        /* No break */
    /** - Master Transmitting Address, received NACK
     *    Either for a Write or Read request, there is a chance the
     *    slave address does not match any of those connected to the
     *    bus.
     *    o Cancel by sending STOP condition.
     *    o Returns back to slave mode.
     *
     */
    case TW_MR_SLA_NACK:              // 0x48
    case TW_MT_SLA_NACK:              // 0x20
        tbf.bits.btwen  = TW_BIT_ON;
        tbf.bits.btwsta = TW_BIT_OFF;
        tbf.bits.btwsto = TW_BIT_ON;  // STOP condition sent.
        tbf.bits.btwea  = TW_BIT_ON;  // Allows address recognition.
        tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
        twiInProgress   = FALSE;
        break;
    /** - Master losing control at SLA+R/W, becoming slave
     *    Happens when the SLA+R/W and ACK were already transfered/received,
     *    but arbitration was lost.
     *    o Returns to slave mode.
     *
     */
    case TW_SR_ARB_LOST_GCALL_ACK:    // 0x78
    case TW_SR_ARB_LOST_SLA_ACK:      // 0x68
        tbf.bits.btwen  = TW_BIT_ON;
        tbf.bits.btwsto = TW_BIT_OFF;
        tbf.bits.btwea  = TW_BIT_ON;  // Allows ACK response.
        tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
        twiInProgress   = FALSE;
        break;

    /* - Slave received its address or global call ( if enabled )
     *   and returned ACK.\n
     *   - clear TWINT to receive data and set TWEA to be able
     *     to ACK it.\n
     */
    case TW_SR_GCALL_ACK:             // 0x70
    case TW_SR_SLA_ACK:               // 0x60
        tbf.bits.btwen  = TW_BIT_ON;
        tbf.bits.btwsto = TW_BIT_OFF;
        tbf.bits.btwea  = TW_BIT_ON;
        tbf.bits.btwint = TW_BIT_ON;
        twiRxDataLen    = 0;          // New Data will arrive
        twiRxDataIdx    = 0;
        twiInProgress   = FALSE;
        break;
    /** - Slave received data and sends ACK\n
     */
    case TW_SR_DATA_ACK:              // 0x80
    case TW_SR_GCALL_DATA_ACK:        // 0x90
        if ( twiRxDataLen < MAX_TW_RX_DATA )
        {
            twiRxDataBuffer[ twiRxDataLen++ ] = TWDR;
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_ON;
            tbf.bits.btwint = TW_BIT_ON;
            twiInProgress   = FALSE;
        }
        else
        {
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_OFF; // NACK, can't handle
                                          // more data
            tbf.bits.btwint = TW_BIT_ON;
            twiInProgress   = FALSE;
        }
        break;
    /** - Returns back to idle slave mode.\n
     *    No operations are currently being executed.\n
     */
    case TW_SR_GCALL_DATA_NACK:       // 0x98
    case TW_ST_DATA_NACK:             // 0xC0
    case TW_SR_DATA_NACK:             // 0x88
        /* No break */
    /** - slave receiving data gets STOP or repeated START
     *    condition\n
     *    - Restarts slave mode to idle state, until its
     *    address is recognized again.\n
     */

    case TW_SR_STOP:                  // 0xA0
        tbf.bits.btwen  = TW_BIT_ON;
        tbf.bits.btwsta = TW_BIT_OFF;
        tbf.bits.btwsto = TW_BIT_OFF;
        tbf.bits.btwea  = TW_BIT_ON;  // Allows address recognition
        tbf.bits.btwint = TW_BIT_ON;
        twiInProgress   = FALSE;
        break;
    /** - From Master transmitting to slave transmitting\n
     *    Arbitration lost.\n
     */
    case TW_ST_ARB_LOST_SLA_ACK:      // 0xB0
        /* No break */
    /** - Slave acknowledged the address, data transfer starts\n
     */
    case TW_ST_SLA_ACK:               // 0xA8
        twiRxDataIdx    = 0;
        /* No break */
    case TW_ST_DATA_ACK:              // 0xB8
        if ( ( twiRxDataLen ) && ( ( twiRxDataLen - 1 ) > twiRxDataIdx ) )
        {
            TWDR = twiRxDataBuffer[ twiRxDataIdx++ ];
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_ON; // Allows ACK reply
            tbf.bits.btwint = TW_BIT_ON;
            twiInProgress   = FALSE;
        }
        else if ( twiRxDataLen > twiRxDataIdx )
        {
            TWDR = twiRxDataBuffer[ twiRxDataIdx++ ];
            tbf.bits.btwen  = TW_BIT_ON;
            tbf.bits.btwsto = TW_BIT_OFF;
            tbf.bits.btwea  = TW_BIT_OFF; // Last byte sends NACK
            tbf.bits.btwint = TW_BIT_ON;
            twiInProgress   = FALSE;
        }
        else
        {
            //TODO
        }
        break;

    /** - Arbitration Lost\n
     *    When the master loses control over the bus.\n
     *    - Slave Mode entered\n
     *    - Does not hold SCL low by clearing TWINT.\n
     */
    case TW_MT_ARB_LOST:              // 0x38
//    case TW_MR_ARB_LOST:            // 0x38
        tbf.bits.btwen  = TW_BIT_ON;
        tbf.bits.btwsta = TW_BIT_OFF;
        tbf.bits.btwsto = TW_BIT_OFF;
        tbf.bits.btwint = TW_BIT_ON;  // Must be cleared to proceed.
        twiInProgress   = FALSE;
        break;
    /** - State no information available\n
     *    This state will only occur while TWINT is off, therefore this
     *    won't occur in an interrupt implementation.\n
     *    - Do nothing, no operation is running.\n
     */
    case TW_NO_INFO:                  // 0xF8
        break;
    /** - Bus Error\n
     *    The error status is achieved when a START or a STOP condition
     *    is sent at an illegal position, such as a data/address transfer,
     *    or ACK transfer/reception.\n
     *    - To recover from error sent STOP condition.\n
     */
    case TW_BUS_ERROR:                // 0x00
        tbf.bits.btwsta = TW_BIT_OFF;
        tbf.bits.btwsto = TW_BIT_ON;  // Sends STOP condition.
        tbf.bits.btwea  = TW_BIT_ON;  // Allows address recognition.
        tbf.bits.btwint = TW_BIT_ON;
        twiInProgress   = FALSE;
        break;
    default:
        break;


    }

    TWCR = tbf.byte;
    return ret;
}
/**
 * @}
 */
/*---------------------------------------------------------------------------*/
