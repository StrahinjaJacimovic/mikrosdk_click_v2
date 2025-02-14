/*!
 * @file main.c
 * @brief MrAngle Click example
 *
 * # Description
 * This library contains API for the MR Angle click driver.
 * This demo application shows an example of angle measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app performs default settings.
 *
 * ## Application Task
 * This is an example that shows the use of an MR Angle click board™.
 * The application task consists of reading the angle measurements in degrees ( 0 - 180 ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mrangle.h"

static mrangle_t mrangle;
static log_t logger;
static float angle;

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    mrangle_cfg_t mrangle_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    mrangle_cfg_setup( &mrangle_cfg );
    MRANGLE_MAP_MIKROBUS( mrangle_cfg, MIKROBUS_1 );
    err_t init_flag  = mrangle_init( &mrangle, &mrangle_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    mrangle_default_cfg ( &mrangle );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void ) {
    mrangle_get_angle( &mrangle, &angle );
    log_printf( &logger, "   Angle : %.2f degree   \r\n", angle );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
