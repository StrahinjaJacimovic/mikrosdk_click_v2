\mainpage Main Page
 
 

---
# Touchkey 2 click

TouchKey 2 click has four capacitive pads powered by Microchip's ATtiny817 which has an integrated touch QTouch® controller.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchkey2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/touchkey-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : UART type


# Software Support

We provide a library for the Touchkey2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Touchkey2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchkey2_cfg_setup ( touchkey2_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHKEY2_RETVAL touchkey2_init ( touchkey2_t *ctx, touchkey2_cfg_t *cfg );

- Click Default Configuration function.
> void touchkey2_default_cfg ( touchkey2_t *ctx );


#### Example key functions :

- Set reset pin function.
> void touchkey2_set_reset_pin ( touchkey2_t *ctx );
 
- Clear reset pin function.
> void touchkey2_clear_reset_pin ( touchkey2_t *ctx );

- Reset function.
> void touchkey2_target_reset ( touchkey2_t *ctx );

## Examples Description
 
> This application is touch controller. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchkey2_cfg_setup( &cfg );
    TOUCHKEY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey2_init( &touchkey2, &cfg );
}
```

### Application Task

> Checks if new data byte have received in rx buffer (ready for reading),
  and if ready than reads one byte from rx buffer, that show if and what key is pressed. 

```c
void application_task ( void )
{
    char tmp;

    tmp = touchkey2_generic_single_read( &touchkey2 );
    
    if( tmp == 0x00 )
    {
        log_printf( &logger, "   Key released   %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x01 )
    {
        log_printf( &logger, "   Key A pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x02 )
    {
        log_printf( &logger, "   Key B pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x04 )
    {
        log_printf( &logger, "   Key C pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x08 )
    {
        log_printf( &logger, "   Key D pressed \r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "   Error!!!   " );
        touchkey2_target_reset( &touchkey2 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchkey2

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
