
---
# ROTARY O click

Rotary click carries a 15-pulse incremental rotary encoder with detents, surrounded by a ring of 16 orange LEDs. It’s a perfect solution for adding a precision input knob to your design. The encoder outputs A and B signals (out of phase to each other); the knob also acts as a push-button which sends an interrupt to the target board MCU. The LED ring is controlled through SPI lines (CS, SCK, MISO, MOSI). Rotary click can be used with either a 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryo_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rotary-o-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RotaryO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RotaryO Click driver.

#### Standard key functions :

- `rotaryo_cfg_setup` Config Object Initialization function.
```c
void rotaryo_cfg_setup ( rotaryo_cfg_t *cfg );
```

- `rotaryo_init` Initialization function.
```c
err_t rotaryo_init ( rotaryo_t *ctx, rotaryo_cfg_t *cfg );
```

#### Example key functions :

- `rotaryo_generic_transfer` ROTARY O data transfer function.
```c
void rotaryo_generic_transfer ( rotaryo_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

- `rotaryo_turn_on_led_by_data` Function turn on led by data.
```c
void rotaryo_turn_on_led_by_data ( rotaryo_t *ctx, uint16_t write_data );
```

- `rotaryo_turn_on_led_by_position` Function turn on led by position
```c
void rotaryo_turn_on_led_by_position ( rotaryo_t *ctx, uint8_t led_position );
```

## Example Description

> The demo application controls led on click with rotory on board

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver, set initial states, set RST logic high and performs device configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryo_cfg_t rotaryo_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    rotaryo_cfg_setup( &rotaryo_cfg );
    ROTARYO_MAP_MIKROBUS( rotaryo_cfg, MIKROBUS_1 );
    err_t init_flag  = rotaryo_init( &rotaryo, &rotaryo_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    
    led_data = 0x0001;
    old_state = 0;
    new_state = 1;
    old__rot_state = 0;
    new_rotate_state = 1;
}

```

### Application Task

> Show functionality of Rotary O Click, rotating and turn on/off led's, using the SPI interface

```c

void application_task ( void ) {
    rotaryo_turn_on_led_by_data( &rotaryo, led_data );

//     Push button
    if ( rotaryo_button_push( &rotaryo ) ) {
        new_state = 1;
        if ( new_state == 1 && old_state == 0 ) {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 ) {
                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryo_turn_on_led_by_data( &rotaryo, 0xAAAA );
                    Delay_ms( 100 );
                    rotaryo_turn_on_led_by_data( &rotaryo, 0x5555 );
                    Delay_ms( 100 );
                }

                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryo_turn_on_led_by_position( &rotaryo, old_state );
                    Delay_ms( 100 );
                }

                led_state = 0;
                led_data = rotaryo_get_led_data( led_state );
            }
            else {
                led_data = rotaryo_get_led_data( led_state );
            }
        }
    }
    else {
        old_state = 0;
    }

//     Rotate Clockwise and CounterClockwise
    if ( rotaryo_get_eca_state( &rotaryo ) == rotaryo_get_ecb_state( &rotaryo ) ) {
        old__rot_state = 0;
        start_status = rotaryo_get_eca_state( &rotaryo ) && rotaryo_get_ecb_state( &rotaryo );
    }
    else {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state ) {
            old__rot_state = 1;
            if ( start_status != rotaryo_get_eca_state( &rotaryo ) ) {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
}

```

## Note

> In order to use all of the clicks functionality, pull down INT pin.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
