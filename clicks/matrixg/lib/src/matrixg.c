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
 * @file matrixg.c
 * @brief Matrix G Click Driver.
 */

#include "matrixg.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MATRIXG_DUMMY 0

// ------------------------------------------------------------------ CONSTANTS

static const uint8_t matrix_ascii[][ 8 ] = 
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // space -- 32
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08 },   // ! -- 33
    { 0x00, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x40 },   // " -- 34
    { 0x00, 0x14, 0x14, 0x3E, 0x14, 0x3E, 0x14, 0x54 },   // # -- 35
    { 0x00, 0x08, 0x1E, 0x28, 0x1C, 0x0A, 0x3C, 0x08 },   // $ -- 36
    { 0x00, 0x30, 0x32, 0x04, 0x08, 0x10, 0x26, 0x46 },   // % -- 37
    { 0x00, 0x18, 0x24, 0x28, 0x10, 0x2A, 0x24, 0x5A },   // & -- 38
    { 0x00, 0x0C, 0x04, 0x08, 0x00, 0x00, 0x00, 0x40 },   // ' -- 39
    { 0x00, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08 },   // ( -- 40
    { 0x00, 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08 },   // ) -- 41
    { 0x00, 0x00, 0x08, 0x1C, 0x3E, 0x1C, 0x08, 0x00 },   // * -- 42
    { 0x00, 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 },   // + -- 43
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10 },   // , -- 44
    { 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00 },   // - -- 45
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 },   // . -- 46
    { 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 },   // / -- 47
    { 0x00, 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C },   // 0 -- 48
    { 0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08 },   // 1 -- 49
    { 0x00, 0x1C, 0x22, 0x02, 0x0C, 0x10, 0x20, 0x3E },   // 2 -- 50
    { 0x00, 0x1C, 0x22, 0x02, 0x0C, 0x02, 0x22, 0x1C },   // 3 -- 51
    { 0x00, 0x04, 0x0C, 0x14, 0x24, 0x1E, 0x04, 0x04 },   // 4 -- 52
    { 0x00, 0x3E, 0x20, 0x20, 0x3E, 0x02, 0x02, 0x7E },   // 5 -- 53
    { 0x00, 0x0C, 0x10, 0x20, 0x3C, 0x22, 0x22, 0x1C },   // 6 -- 54
    { 0x00, 0x3E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x50 },   // 7 -- 55
    { 0x00, 0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x5C },   // 8 -- 56
    { 0x00, 0x1C, 0x22, 0x22, 0x1E, 0x02, 0x02, 0x5C },   // 9 -- 57
    { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00 },   // : -- 58
    { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x10 },   // ; -- 59
    { 0x00, 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04 },   // < -- 60
    { 0x00, 0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x00 },   // = -- 61
    { 0x00, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10 },   // > -- 62
    { 0x00, 0x1C, 0x22, 0x02, 0x0C, 0x08, 0x00, 0x08 },   // ? -- 63
    { 0x00, 0x1C, 0x22, 0x02, 0x1A, 0x2A, 0x2A, 0x1C },   // @ -- 64
    { 0x00, 0x1C, 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22 },   // A -- 65
    { 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x22, 0x22, 0x3C },   // B -- 66
    { 0x00, 0x1C, 0x22, 0x20, 0x20, 0x20, 0x22, 0x1C },   // C -- 67
    { 0x00, 0x38, 0x24, 0x22, 0x22, 0x22, 0x24, 0x38 },   // D -- 68
    { 0x00, 0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x3E },   // E -- 69
    { 0x00, 0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x20 },   // F -- 70
    { 0x00, 0x1C, 0x22, 0x20, 0x2E, 0x22, 0x22, 0x1E },   // G -- 71
    { 0x00, 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22 },   // H -- 72
    { 0x00, 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C },   // I -- 73
    { 0x00, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x24, 0x18 },   // J -- 74
    { 0x00, 0x22, 0x24, 0x28, 0x30, 0x28, 0x24, 0x22 },   // K -- 75
    { 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E },   // L -- 76
    { 0x00, 0x22, 0x36, 0x2A, 0x2A, 0x22, 0x22, 0x22 },   // M -- 77
    { 0x00, 0x22, 0x22, 0x32, 0x2A, 0x26, 0x22, 0x22 },   // N -- 78
    { 0x00, 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C },   // O -- 79
    { 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20 },   // P -- 80
    { 0x00, 0x1C, 0x22, 0x22, 0x22, 0x2A, 0x24, 0x1A },   // Q -- 81
    { 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x28, 0x24, 0x22 },   // R -- 82
    { 0x00, 0x1E, 0x20, 0x20, 0x1C, 0x02, 0x02, 0x3C },   // S -- 83
    { 0x00, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 },   // T -- 84
    { 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C },   // U -- 85
    { 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08 },   // V -- 86
    { 0x00, 0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x14 },   // W -- 87
    { 0x00, 0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22 },   // X -- 88
    { 0x00, 0x22, 0x22, 0x22, 0x1C, 0x08, 0x08, 0x08 },   // Y -- 89
    { 0x00, 0x3E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x3E },   // Z -- 90
    { 0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30 },   // [ -- 91
    { 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 },   // \ -- 92
    { 0x00, 0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0E },   // ] -- 93
    { 0x00, 0x08, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00 },   // ^ -- 94
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E },   // _ -- 95
    { 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },   // ` -- 96
    { 0x00, 0x00, 0x00, 0x1C, 0x02, 0x1E, 0x22, 0x1E },   // a -- 97
    { 0x00, 0x20, 0x20, 0x20, 0x2C, 0x32, 0x22, 0x3C },   // b -- 98
    { 0x00, 0x00, 0x00, 0x3C, 0x20, 0x20, 0x22, 0x3C },   // c -- 99
    { 0x00, 0x02, 0x02, 0x02, 0x1A, 0x26, 0x22, 0x1E },   // d -- 100
    { 0x00, 0x00, 0x00, 0x1C, 0x22, 0x3E, 0x20, 0x1C },   // e -- 101
    { 0x00, 0x0C, 0x12, 0x10, 0x38, 0x10, 0x10, 0x10 },   // f -- 102
    { 0x00, 0x00, 0x1E, 0x22, 0x22, 0x1E, 0x02, 0x1C },   // g -- 103
    { 0x00, 0x20, 0x20, 0x20, 0x2C, 0x32, 0x22, 0x22 },   // h -- 104
    { 0x00, 0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08 },   // i -- 105
    { 0x00, 0x04, 0x00, 0x0C, 0x04, 0x04, 0x24, 0x18 },   // j -- 106
    { 0x00, 0x20, 0x20, 0x24, 0x28, 0x30, 0x28, 0x24 },   // k -- 107
    { 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C },   // l -- 108
    { 0x00, 0x00, 0x00, 0x34, 0x2A, 0x2A, 0x22, 0x22 },   // m -- 109
    { 0x00, 0x00, 0x00, 0x2C, 0x32, 0x22, 0x22, 0x22 },   // n -- 110
    { 0x00, 0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C },   // o -- 111
    { 0x00, 0x00, 0x00, 0x3C, 0x22, 0x3C, 0x20, 0x20 },   // p -- 112
    { 0x00, 0x00, 0x00, 0x1A, 0x26, 0x1E, 0x02, 0x02 },   // q -- 113
    { 0x00, 0x00, 0x00, 0x2C, 0x32, 0x20, 0x20, 0x20 },   // r -- 114
    { 0x00, 0x00, 0x00, 0x1C, 0x20, 0x1C, 0x02, 0x3C },   // s -- 115
    { 0x00, 0x10, 0x10, 0x38, 0x10, 0x10, 0x12, 0x0C },   // t -- 116
    { 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x26, 0x1A },   // u -- 117
    { 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x14, 0x28 },   // v -- 118
    { 0x00, 0x00, 0x00, 0x22, 0x22, 0x2A, 0x2A, 0x1C },   // w -- 119
    { 0x00, 0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22 },   // x -- 120
    { 0x00, 0x00, 0x00, 0x22, 0x22, 0x1E, 0x02, 0x1C },   // y -- 121
    { 0x00, 0x00, 0x00, 0x3E, 0x04, 0x08, 0x10, 0x3E }    // z -- 121
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_display_left ( matrixg_t *ctx, uint8_t row, uint8_t column );

static void dev_display_right ( matrixg_t *ctx, uint8_t row, uint8_t column );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void matrixg_cfg_setup ( matrixg_cfg_t *cfg ) {
    
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->csn = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MATRIXG_RETVAL matrixg_init ( matrixg_t *ctx, matrixg_cfg_t *cfg ) {
   
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MATRIXG_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
       
        return MATRIXG_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MATRIXG_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->csn , cfg->csn );

    return MATRIXG_OK;
}

void matrixg_display_characters ( matrixg_t *ctx, uint8_t left_char, uint8_t right_char ) {
   
    int8_t i;
  
    for( i = 7; i >= 0; i-- ) {
       
        dev_display_left( ctx, matrix_ascii[ left_char - 32 ][ i ], 7 - i );
    }

    for( i = 7; i >= 0; i-- ) {
        
        dev_display_right( ctx, matrix_ascii[ right_char - 32 ][ i ], 7 - i );
    }
}

void matrixg_write_reg ( matrixg_t *ctx, uint8_t address, uint8_t input_data ) {
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &address, 1 );
    spi_master_write( &ctx->spi, &input_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    digital_out_low( &ctx->csn );
    spi_master_write( &ctx->spi, &address, 1 );
    spi_master_write( &ctx->spi, &input_data, 1 );
    digital_out_high( &ctx->csn );
}

void matrixg_default_cfg ( matrixg_t *ctx ) {
    
    matrixg_write_reg( ctx, MATRIXG_DECODE_MODE_REG, MATRIXG_NO_DECODE );
    matrixg_write_reg( ctx, MATRIXG_INTENSITY_REG, MATRIXG_INTEN_LVL_3 );
    matrixg_write_reg( ctx, MATRIXG_SCAN_LIMIT_REG, MATRIXG_DISPLAY_DIGIT_0_6 );
    matrixg_write_reg( ctx, MATRIXG_SHUTDOWN_REG, MATRIXG_NORMAL_OPERATION ); 
}

void matrixg_set_csn_high ( matrixg_t *ctx ) {
    
    digital_out_high( &ctx->csn );
}

void matrixg_set_csn_low ( matrixg_t *ctx ) {
    
    digital_out_low( &ctx->csn );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_display_left ( matrixg_t *ctx, uint8_t row, uint8_t column ) {
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &++column, 1 );
    spi_master_write( &ctx->spi, &row, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void dev_display_right ( matrixg_t *ctx, uint8_t row, uint8_t column ) {
    
    digital_out_low( &ctx->csn );
    spi_master_write( &ctx->spi, &++column, 1 );
    spi_master_write( &ctx->spi, &row, 1 );
    digital_out_high( &ctx->csn );
}

// ------------------------------------------------------------------------- END

