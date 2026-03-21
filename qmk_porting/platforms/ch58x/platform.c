/*
Copyright 2022 Huckies <https://github.com/Huckies>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "platform_deps.h"
#include <stdio.h>
#include "HAL.h"
#include "gpio.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "extra_keycode.h"
#include "bootloader.h"
#include "hidkbd.h"

volatile uint8_t kbd_protocol_type = 0;
#if defined BLE_ENABLE || (defined ESB_ENABLE && (ESB_ENABLE == 1 || ESB_ENABLE == 2))
extern void wireless_indicator_status_reset();
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

#endif

#if defined BLE_ENABLE || (defined ESB_ENABLE && (ESB_ENABLE == 1 || ESB_ENABLE == 2))
extern Device_Info_ g_device_info;

bool wireless_process_record(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case BLE_SLOT0 ...(BLE_SLOT0 + BLE_SLOT_NUM - 1):
            if (record->event.pressed) {
                if (kbd_protocol_type == kbd_protocol_ble)
                {
                    connectAnotherDevice(keycode - BLE_SLOT0);
                } else {
                    bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_BLE);
                    soft_reset_keyboard();
                }
            }
            return false;
        case BLE_ALL_CLEAR:
        {
            GAPBondMgr_SetParameter(GAPBOND_ERASE_ALLBONDS, 0, NULL);

            EEPROM_ERASE(USER_EEPROM_START_POSITION + DEVICE_INFO_EEPROM_OFFSET, EEPROM_PAGE_SIZE);
            return false;
        }
    }
    return true;
}
#endif

__HIGH_CODE _PUTCHAR_CLAIM;

int8_t sendchar(uint8_t c)
{
    _putchar(c);
    return 0;
}

#if !defined ESB_ENABLE || ESB_ENABLE == 1
bool shutdown_kb(bool jump_to_bootloader)
{
    rgbled_power_off();
// #if defined BLE_ENABLE || (defined ESB_ENABLE && (ESB_ENABLE == 1 || ESB_ENABLE == 2))
//     wireless_indicator_status_reset();
// #endif

#ifdef ENCODER_ENABLE
    pin_t encoders_pad_a[] = ENCODER_A_PINS, encoders_pad_b[] = ENCODER_B_PINS;

    for (uint8_t i = 0; i < sizeof(encoders_pad_a) / sizeof(encoders_pad_a[0]); i++) {
        gpio_set_pin_input_low(encoders_pad_a[i]);
    }
    for (uint8_t i = 0; i < sizeof(encoders_pad_b) / sizeof(encoders_pad_b[0]); i++) {
        gpio_set_pin_input_low(encoders_pad_b[i]);
    }
#endif

    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }

    return true;
}
#endif

void platform_setup()
{
#if LSE_ENABLE
    R16_PIN_ANALOG_IE |= RB_PIN_XT32K_IE;
#endif
#ifdef PLF_DEBUG
    DBG_INIT;
    PRINT("App " MACRO2STR(__GIT_VERSION__) ", build on %s\r\n", QMK_BUILDDATE);
#else
    gpio_write_pin_high(A9);
    gpio_set_pin_output(A9);
    gpio_set_pin_input_high(A8);
    UART1_DefInit();
    UART1_BaudRateCfg(DEBUG_BAUDRATE);

    char buffer[UINT8_MAX];
    uint8_t len = sprintf(buffer, "App " MACRO2STR(__GIT_VERSION__) ", build on %s\r\n", QMK_BUILDDATE);

    while (len) {
        if (R8_UART1_TFC != UART_FIFO_SIZE) {
            R8_UART1_THR = buffer[strlen(buffer) - len];
            len--;
        }
    }
    while ((R8_UART1_LSR & RB_LSR_TX_ALL_EMP) == 0) {
        __nop();
    }
    R8_UART1_IER = RB_IER_RESET;
    gpio_set_pin_input_low(A8);
    gpio_set_pin_input_low(A9);
#endif

    {
        // preserve BOOTMAGIC_ROW and BOOTMAGIC_COLUMN to eeprom for future use
        uint8_t buffer[EEPROM_PAGE_SIZE], ret;

        do {
            ret = EEPROM_READ(QMK_EEPROM_RESERVED_START_POSITION, buffer, sizeof(buffer));
        } while (ret);
        if (buffer[1] != BOOTMAGIC_ROW || buffer[2] != BOOTMAGIC_COLUMN) {
            buffer[1] = BOOTMAGIC_ROW;
            buffer[2] = BOOTMAGIC_COLUMN;
            do {
                ret = EEPROM_ERASE(QMK_EEPROM_RESERVED_START_POSITION, EEPROM_PAGE_SIZE) ||
                      EEPROM_WRITE(QMK_EEPROM_RESERVED_START_POSITION, buffer, EEPROM_PAGE_SIZE);
            } while (ret);
        }
    }

    bootloader_select_boot_mode();

    ch582_interface_t *interface = ch582_get_protocol_interface();

    if (interface) {
        interface->ch582_platform_initialize();
    }
}
