/*
Copyright 2022 Huckies <https://github.com/Huckies>
Copyright 2023 OctopusZ <https://github.com/OctopusZ>

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

#include QMK_KEYBOARD_H

const uint32_t PROGMEM unicode_map[] = {
    // [la] = 0x03B1, // α
    // [lA] = 0x0307, //
    // [lb] = 0x03B2, // β
    // [lB] = 0x2229, // ∩
    // [rc] = 0x2284, // ⊄
    // [rC] = 0x2286, // ⊆
    // [rv] = 0x2285, // ⊅
    // [rV] = 0x2287, //⊇
    // [rb] = 0x2227, // ∧
    // [rB] = 0x22BC, //⊼
    // [rn] = 0x2228, //∨
    // [rN] = 0x22BB  //⊻
};

int main()
{
    extern void protocol_setup();
    extern void protocol_pre_init();
    extern void protocol_post_init();
    extern void platform_run();

    platform_setup();

    protocol_setup();
#if !defined ESB_ENABLE || ESB_ENABLE != 2
    keyboard_setup();
#endif

    protocol_pre_init();
    keyboard_init();
    protocol_post_init();

    /* Main loop */
    for (;;) {
        platform_run();
        //! housekeeping_task() is handled by platform
    }
}
