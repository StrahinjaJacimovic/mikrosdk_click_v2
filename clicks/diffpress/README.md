\mainpage Main Page
 
---
# Diff Press click

Diff Press Click is an accurate pressure sensor Click board™ capable of measuring differential pressure.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/diffpress_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/diff-press-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the DiffPress Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DiffPress Click driver.

#### Standard key functions :
 
- Initialization function.
> DIFFPRESS_RETVAL diffpress_init ( diffpress_t *ctx, diffpress_cfg_t *cfg );

#### Example key functions :

- Gets adc data function.
> uint16_t diffpress_get_adc_data( diffpress_t *ctx );
 
- Gets pressure difference function.
> float diffpress_get_pressure_difference( diffpress_t *ctx );

## Examples Description

> This demo application is made for measuring differential pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and logger module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpress_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    diffpress_cfg_setup( &cfg );
    DIFFPRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    diffpress_init( &diffpress, &cfg );
}
```

### Application Task

> Logs pressure difference data. 

```c

void application_task ( void )
{
    pressure_difference = diffpress_get_pressure_difference( &diffpress );

    log_printf( &logger, "-- Pressure difference  : %f kPa\r\n", pressure_difference );

    Delay_ms( 100 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress

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
