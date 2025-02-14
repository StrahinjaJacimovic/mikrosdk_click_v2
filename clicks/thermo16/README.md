\mainpage Main Page
 
 

---
# Thermo 16 click

Thermo 16 Click is a Click board equipped with the sensor IC, which can measure temperature measurements between -40°C and +150°C so that the temperature measurement data can be processed by the host MCU. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-16-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Thermo16 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo16 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo16_cfg_setup ( thermo16_cfg_t *cfg ); 
 
- Initialization function.
> THERMO16_RETVAL thermo16_init ( thermo16_t *ctx, thermo16_cfg_t *cfg );

#### Example key functions :

-  Temperature function.
> float thermo16_get_temperature ( thermo16_t *ctx, uint8_t temp_format );
 
- Generic read function.
> thermo16_data_t thermo16_generic_read ( thermo16_t *ctx );

## Examples Description

>  This demo-app shows the temperature measurement procedure using Thermo 16 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo16_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermo16_cfg_setup( &cfg );
    THERMO16_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo16_init( &thermo16, &cfg );
}
```

### Application Task

> Reads ambient temperature data and this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temp;
    
    //  Task implementation.
    
    temp = thermo16_get_temperature ( &thermo16, THERMO16_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature : %.2f C \r\n", temp );
    
    Delay_ms( 1500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo16

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
