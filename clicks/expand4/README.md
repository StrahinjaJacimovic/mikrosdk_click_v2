\mainpage Main Page
 
 

---
# Expand 4 click

Expand 4 click carries TPCIC6A595, a chip that combines an 8-bit serial-in, parallel-out shift register with an 8-bit D-type storage register.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Expand4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand4_cfg_setup ( expand4_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND4_RETVAL expand4_init ( expand4_t *ctx, expand4_cfg_t *cfg );

- Click Default Configuration function.
> void expand4_default_cfg ( expand4_t *ctx );


#### Example key functions :

- Function write 8-bit data function to TPIC6A595 shift register.
> void expand4_write_data( expand4_t *ctx, uint8_t write_command );
 
- Function turn on output buffers - set PWM pin low
> void expand4_enable_output( expand4_t *ctx );

- Function clear input TPIC6A595 shift register.
> void expand4_reset( expand4_t *ctx );

## Examples Description

> Example demonstrates use of Expand 4 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - Clear TPIC6A595 register and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand4_cfg_setup( &cfg );
    EXPAND4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand4_init( &expand4, &cfg );
    expand4_reset( &expand4 );
}
  
```

### Application Task

> This is a example which demonstrates the use of Expand 4 Click board.
> In this example, the LED pin mask is transferred via SPI bus,
> LEDs connected to D0-D7 pins are lit accordingly by turning ON LEDs from D0 to D7 for 3 sec.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec. when the change pin who is connected.

```c

void application_task ( void )
{
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand4_disable_output( &expand4 );
        Delay_ms( 100 );

        expand4_turn_on_by_position( &expand4, pin_position );
        Delay_ms( 100 );

        log_printf( &logger, " D%d", pin_position );

        expand4_enable_output( &expand4 );
        Delay_ms( 3000 );
    }

    log_printf( &logger, "\n----------------------------------\n");
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
