\mainpage Main Page
 
 

---
# DC Motor 10 click

DC Motor 10 Click is a brushed DC motor driver with the current limiting and current sensing. It is based on the TLE 6208-6 G, an Hex-Half-Bridge / Double Six-Driver IC,
optimized for motor driving applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-10-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DcMotor10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor10_cfg_setup ( dcmotor10_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR10_RETVAL dcmotor10_init ( dcmotor10_t *ctx, dcmotor10_cfg_t *cfg );


#### Example key functions :

- Function is used to send command.
> void dcmotor10_send_cmd ( dcmotor10_t *ctx, uint16_t wr_data );
 
- Function is used to read status.
> uint16_t dcmotor10_read_status ( dcmotor10_t *ctx );

- Function is used to inhibit or uninhibit the device.
> void dcmotor10_inhibit ( dcmotor10_t *ctx, uint8_t state );

## Examples Description

> 
> This example is running dc motors on channels 1 through 3.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes SPI, click drivers and uninhibites the device.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor10_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor10_cfg_setup( &cfg );
    DCMOTOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor10_init( &dcmotor10, &cfg );
    Delay_ms( 100 );
    
    dcmotor10_inhibit(&dcmotor10, DCMOTOR10_UNINHIBIT );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
    Delay_ms( 100 );
}
  
```

### Application Task

>
> This example demonstrates the use of DC MOTOR 10 click by running dc motors 
> on channels 1 through 3, first all 3 together and then separately.
> 

```c

void application_task ( void )
{
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 | DCMOTOR10_ENABLE_2 
                      | DCMOTOR10_ENABLE_3 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_2 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_3 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor10

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
