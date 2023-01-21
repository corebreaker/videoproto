/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  PIC24FJ256GB106
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "./mcc_generated_files/system.h"
#include "./mcc_generated_files/interrupt_manager.h"
#include "./mcc_generated_files/tmr2.h"
#include "./mcc_generated_files/tmr3.h"

#include "./delay.h"
#include "./app/connect_state.h"
#include "./app/leds.h"
#include "./app/app.h"

#include "./logger/logger.h"
#include "./mcc_generated_files/pin_manager.h"
#include "./app/leds.h"

#include "./mcc_generated_files/i2c1_driver.h"

// USB connection monitoring
static void usb_connection(bool connected) {
    led_ready(connected);
}

static bool pushed = false;
static void handler() {
    if (EXT_APPLY_GetValue()) {
        pushed = true;
        return;
    }

    if (pushed) {
        logger_send_event(2);
        pushed = false;
    }
}

static void app_log(void) {
    led_signal_activate(LED_SIGNAL_PROG, 0);
}

static void dummy(void) {}

static bool eotFlag = false;

static bool waitForAck(void) {
    for (int i = 0; i < 1000000; i++) {
        if (eotFlag) {
            eotFlag = false;
            led_signal_activate(LED_SIGNAL_FLASH, 0);

            return true;
        }
    }
    
    return false;
}

static void intHandler(void) {
    if (!i2c1_driver_isBuferFull()) {
        eotFlag = true;
    }

    i2c1_clearIRQ();
}

static void sendCode(uint8_t *d, uint8_t sz) {
    i2c1_driver_start();

    i2c1_driver_TXData(0x40);
    i2c1_waitForEvent(NULL);
    led_signal_activate(LED_SIGNAL_PROG, 0);
    /*if (!waitForAck()) {
        led_signal_activate(LED_SIGNAL_ERROR, 0);
        return;
    }*/
    
    for (uint8_t i = 0; i < sz; i++) {
        i2c1_driver_TXData(d[1]);
        i2c1_waitForEvent(NULL);
        /*if (!waitForAck()) {
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            return;
        }*/
    }
    
    i2c1_driver_sendACK();
    i2c1_driver_stop();

    led_signal_activate(LED_SIGNAL_READY, 0);
}

/*
   Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    i2c1_driver_setMasterI2cISR(intHandler);
    i2c1_driver_setSlaveI2cISR(dummy);
    i2c1_driver_driver_open();
    i2c1_enableIRQ();

    INTERRUPT_GlobalEnable();

    led_error(true);

    CN_SetInterruptHandler(handler);
    TMR2_SetInterruptHandler(connection_signal_timer);
    TMR3_SetInterruptHandler(led_signal_event);
    set_connecion_state_handler(usb_connection);
    logger_on_push_button(app_log);

    logger_init();
    init_app();

    delay_ms(200);
    led_error(false);
    delay_ms(500);

    uint8_t cmd[] = { 4, 6 };
    sendCode(cmd, sizeof(cmd));

    while (1) {
        app_loop();
    }

    return 1;
}
/**
 End of File
*/

