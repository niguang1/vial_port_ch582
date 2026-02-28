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

#include <stdint.h>
#include <stdbool.h>

/*
 * Handle data received from BLE during IAP (In-Application Programming).
 * This function processes data chunks received over BLE and can perform
 * any necessary preprocessing or validation.
 * 
 * Note: This is a stub implementation. Replace with actual BLE data handling
 * if needed by your wireless library.
 */
#if defined(BLE_ENABLE) || (defined(ESB_ENABLE) && (ESB_ENABLE == 1 || ESB_ENABLE == 2))

__attribute__((section(".highcode"))) 
void iap_handle_data(uint32_t start_address, uint8_t *data, uint32_t len)
{
    /* 
     * TODO: Implement BLE-specific data handling for IAP.
     * This function is called when writing flash during BLE firmware updates.
     * It can be used to perform encryption/decryption, compression handling,
     * or other BLE-specific data transformations.
     * For now, this is a no-op as the main flash write logic handles the data.
     */
    (void)start_address;
    (void)data;
    (void)len;
}

/*
 * Validate application firmware received over BLE.
 * This function checks if the application image is valid before jumping to it.
 * 
 * Note: This is a stub implementation. Return false to use the default
 * MCUboot validation method instead.
 */
__attribute__((section(".highcode")))
bool iap_validate(uint32_t *address)
{
    /*
     * TODO: Implement BLE-specific validation.
     * This function can be used to perform wireless-specific checks
     * on the application image before boot.
     * For now, return false to use the standard MCUboot validation.
     */
    (void)address;
    return false;
}

/*
 * Optional: Called when a new wireless device is being initialized.
 * This allows the IAP bootloader to perform any necessary wireless setup.
 */
__attribute__((section(".highcode")))
void iap_handle_new_wireless_chip(void)
{
    /*
     * TODO: Implement any necessary wireless initialization for a new chip.
     * This is called during the first boot of a newly flashed keyboard.
     */
}

#endif /* BLE_ENABLE || ESB_ENABLE */
