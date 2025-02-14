/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file lr2.c
 * @brief LR 2 Click Driver.
 */

#include "lr2.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void lr2_resp ( lr2_t *ctx );
static uint8_t lr2_par ( lr2_t *ctx );
static uint8_t lr2_repar ( lr2_t *ctx );
static void lr2_write ( lr2_t *ctx );
static void lr2_read ( lr2_t *ctx );
static void lr2_drv_process ( lr2_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lr2_cfg_setup ( lr2_cfg_t *cfg ) {
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t lr2_init ( lr2_t *ctx, lr2_cfg_t *cfg ) {
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins

    digital_in_init( &ctx->cts, cfg->cts );

    return LR2_OK;
}

void lr2_default_cfg ( lr2_t *ctx, bool cb_default, void ( *response_p )( char *response ) ) {
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rts );
    
    memset( ctx->buff.tx_buffer, 0, LR2_MAX_CMD_SIZE + LR2_MAX_DATA_SIZE );
    memset( ctx->buff.rx_buffer, 0, LR2_MAX_RSP_SIZE + LR2_MAX_DATA_SIZE );
    
    ctx->tm.timer_max          = LR2_TIMER_EXPIRED;
    ctx->buff.rx_buffer_len    = 0;
    ctx->tm.ticker             = 0;
    ctx->tm.timer_f            = false;
    ctx->tm.timeout_f          = false;
    ctx->tm.timer_use_f        = false;
    ctx->rsp.rsp_f             = false;
    ctx->flags.rsp_rdy_f       = false;
    ctx->flags.lr2_rdy_f        = true;
    ctx->rsp.callback_resp     = response_p;
    ctx->rsp.callback_default  = cb_default;
    
    Delay_1sec( );
}

void lr2_generic_write ( lr2_t *ctx, char *data_buf, uint16_t len ) {
    uart_write( &ctx->uart, data_buf, len );
}

int32_t lr2_generic_read ( lr2_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lr2_cmd ( lr2_t *ctx, char *cmd,  char *response ) {
    char buf[ ] = "";
    uint8_t *pom = buf;

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    strcpy( ctx->buff.tx_buffer, cmd );

    ctx->rsp.rsp_buffer = response;
    lr2_write( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }
}

uint8_t lr2_mac_tx ( lr2_t *ctx, lr2_mac_t *mac ) {
    uint8_t res = 0;

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    strcpy( ctx->buff.tx_buffer, ( char* )LR2_MAC_TX );
    strcat( ctx->buff.tx_buffer, mac->payload);
    strcat( ctx->buff.tx_buffer, mac->port_no );
    strcat( ctx->buff.tx_buffer, " " );
    strcat( ctx->buff.tx_buffer, mac->buffer );
    ctx->rsp.rsp_buffer = mac->response;
    lr2_write( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    if ( ( res = lr2_par( ctx ) ) ) {
        return res;
    }
    lr2_resp( ctx );

    do {
        while ( !ctx->flags.lr2_rdy_f ) {
            lr2_drv_process( ctx );
        }

    } while ( ( res = lr2_repar( ctx ) ) == 12 );

    return res;
}

uint8_t lr2_join ( lr2_t *ctx, char *join_mode, char *response ) {
    uint8_t res = 0;

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    strcpy( ctx->buff.tx_buffer, ( char* ) LR2_JOIN );
    strcat( ctx->buff.tx_buffer, join_mode );
    ctx->rsp.rsp_buffer = response;
    lr2_write( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    if ( ( res = lr2_par( ctx ) ) ) {
        return res;
    }

    lr2_resp( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    return lr2_repar( ctx );
}

uint8_t lr2_rx ( lr2_t *ctx, char *window_size, char *response ) {
    uint8_t res = 0;

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    strcpy( ctx->buff.tx_buffer, "radio rx " );
    strcat( ctx->buff.tx_buffer, window_size );
    ctx->rsp.rsp_buffer = response;
    lr2_write( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    if ( res = lr2_par( ctx ) ) {
        return res;
    }

    lr2_resp( ctx );

    while ( !ctx->flags.lr2_rdy_f ) {
        lr2_drv_process( ctx );
    }

    return lr2_repar( ctx );
}

uint8_t lr2_tx ( lr2_t *ctx, char *buffer ) {
    uint8_t res = 0;
    
    lr2_drv_process( ctx );
    strcpy( ctx->buff.tx_buffer, "radio tx ");
    strcat( ctx->buff.tx_buffer, buffer );

    lr2_write( ctx );

    lr2_drv_process( ctx );

    if ( ( res = lr2_par( ctx ) ) ) {
        return res;
    }

    lr2_resp( ctx );
    lr2_drv_process( ctx );

    return lr2_repar( ctx );
}

void lr2_rx_isr ( lr2_t *ctx, char rx_input ) {
    ctx->buff.rx_buffer[ ctx->buff.rx_buffer_len++ ] = rx_input;
    if ( rx_input == '\r' ) {
        ctx->buff.rx_buffer[ ctx->buff.rx_buffer_len++ ] = '\0';
        ctx->flags.rsp_rdy_f = true;  
    } 
}

void lr2_tick_isr ( lr2_t *ctx ) {
    if ( ctx->tm.timer_use_f ) {
        if ( ctx->tm.timer_f && ( ctx->tm.ticker++ > ctx->tm.timer_max ) ) {
            ctx->tm.timeout_f = true;
        }
    }
}

void lr2_tick_conf ( lr2_t *ctx, uint32_t timer_limit ) {
    if ( timer_limit ) {
        ctx->tm.timer_max = timer_limit;
        ctx->tm.timer_use_f = true;
    } else {
        ctx->tm.timer_max = LR2_TIMER_EXPIRED;
        ctx->tm.timer_use_f = false;
    }
}

void lr2_isr_process ( lr2_t *ctx ) {
    lr2_rx_isr( ctx, ctx->data_in );

    if ( ctx->flags.rsp_rdy_f ) {        
        lr2_read( ctx );
    }
    if ( ctx->tm.timeout_f ) {
        lr2_read( ctx );
    }
}

void lr2_put_char ( lr2_t *ctx, char data_in ) {
    ctx->data_in = data_in;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void lr2_resp ( lr2_t *ctx ) {
    ctx->buff.rx_buffer_len = 0;
    ctx->flags.lr2_rdy_f = false;
    ctx->flags.rsp_rdy_f  = false;
    ctx->rsp.rsp_f        = true;
}

static uint8_t lr2_par ( lr2_t *ctx ) {
    if ( !strcmp( ctx->buff.rx_buffer, "invalid_param" ) ) {
        return 1;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "not_joined" ) ) {
        return 2;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "no_free_ch" ) ) {
        return 3;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "silent" ) ) {
        return 4;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "frame_counter_err_rejoin_needed" ) ) {
        return 5;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "busy" ) ) {
        return 6;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "mac_paused" ) ) {
        return 7;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "invalid_data_len" ) ) {
        return 8;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "keys_not_init" ) ) {
        return 9;
    }

    return 0; 
}

static uint8_t lr2_repar ( lr2_t *ctx ) {
    if ( !strcmp( ctx->buff.rx_buffer, "mac_err" ) ) {
        return 10;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "mac_tx_ok" ) ) {
        return 0;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "mac_rx" ) ) {
        return 12;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "invalid_data_len" ) ) {
        return 13;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "radio_err" ) ) {
        return 14;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "radio_tx_ok" ) ) {
        return 0;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "radio_rx" ) ) {
        return 0;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "accepted" ) ) {
        return 0;
    }
    if ( !strcmp( ctx->buff.rx_buffer, "denied" ) ) {
        return 18;
    }

    return 0;
}

static void lr2_write ( lr2_t *ctx ) {
    char buff; 
    char *ptr = ctx->buff.tx_buffer;
    

    while ( *ptr ) {
        if ( !digital_in_read( &ctx->cts ) ) {
            lr2_generic_write ( ctx, ptr++, 1 );
        }
    }
    
    buff = 13;
    lr2_generic_write ( ctx, &buff, 1 );
    buff = 10;
    lr2_generic_write ( ctx, &buff, 1 );

    ctx->buff.rx_buffer_len  = 0;
    ctx->flags.lr2_rdy_f    = false;
    ctx->flags.rsp_rdy_f     = false;
    ctx->tm.timer_f          = true;
    ctx->rsp.rsp_f           = true;
}

static void lr2_read ( lr2_t *ctx ) {
    if ( !ctx->rsp.rsp_f ) {
        digital_out_high( &ctx->rts );
        ctx->rsp.callback_resp( ctx->buff.rx_buffer );
        digital_out_low( &ctx->rts );

    } else if ( ctx->rsp.rsp_f ) {
        digital_out_high( &ctx->rts );
        strcpy( ctx->rsp.rsp_buffer, ctx->buff.rx_buffer );
        digital_out_low( &ctx->rts );
    }

    ctx->flags.lr2_rdy_f  = true;
    ctx->flags.rsp_rdy_f   = false;
    ctx->tm.timer_f        = false;
    ctx->rsp.rsp_f         = true;
}

static void lr2_drv_process ( lr2_t *ctx  ) {
    int16_t rsp_size;
    
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = 3;
    
    while ( process_cnt != 0 ) {
        rsp_size = lr2_generic_read( ctx, &uart_rx_buffer, DRV_RX_BUFFER_SIZE );

        if ( rsp_size != -1 ) {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) {
                lr2_put_char( ctx, uart_rx_buffer[ check_buf_cnt ] );
                lr2_isr_process( ctx);
            }

            // Clear RX buffer
            memset( uart_rx_buffer, 0, DRV_RX_BUFFER_SIZE );
        } else {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

// ------------------------------------------------------------------------- END
