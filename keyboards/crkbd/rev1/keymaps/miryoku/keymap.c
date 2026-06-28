// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

// 1/4 - Include header for Miryoku constants (e.g., U_EXTRA, U_BASE)
#include "manna-harbour_miryoku.h"
// Mirror declaration, Referenced from: users/miryoku/manna-harbour_miryoku.c, users/miryoku/miryoku_babel/miryoku_layer_list.h
enum {
    U_TD_BOOT_CUSTOM,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER##_CUSTOM,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// 2/4 - Define custom Tap Dance behavior
void u_td_fn_boot_custom(tap_dance_state_t *state, void *user_data) {
  uprintf("%s: Triggered! count: [%d]\n", __func__, state->count);
  if (state->count == 2) { // Default behavior
    uprintf("%s: Resetting to bootloader\n", __func__);
    reset_keyboard();
  } else if (state->count == 3) {
    uprintf("%s: Resetting MCU\n", __func__);
    soft_reset_keyboard();
  }
}

void u_td_fn_U_EXTRA_custom(tap_dance_state_t *state, void *user_data) {
  uprintf("%s: Triggered! count: [%d]\n", __func__, state->count);
  if (state->count == 2) { // Default behavior
    uprintf("%s: Setting Miryoku EXTRA layer\n", __func__);
    default_layer_set((layer_state_t)1 << U_EXTRA);
  } else if (state->count == 3) {
    uprintf("%s: Toggling SOCD Cleaner\n", __func__);
    keyrecord_t record;
    record.event.pressed = true;
    uint16_t keycode = SOCDTOG;
    // API Format: process_record_<module>
    process_record_socd_cleaner(keycode, &record);
    // uprintf("%s: SOCD en: [%d]\n", __func__, socd_cleaner_enabled);
  }
}

// 3/4 - Declare external reference to the core Miryoku tap_dance_actions array
extern tap_dance_action_t tap_dance_actions[];

void keyboard_post_init_user(void) {
  // 4/4 - Hook into post_init to perform the runtime override
  // Create our custom action struct
  tap_dance_action_t custom_boot_td   = ACTION_TAP_DANCE_FN(u_td_fn_boot_custom);
  tap_dance_action_t custom_extra_td  = ACTION_TAP_DANCE_FN(u_td_fn_U_EXTRA_custom);
  // Patch the Miryoku action table.
  tap_dance_actions[U_TD_BOOT_CUSTOM]     = custom_boot_td;
  tap_dance_actions[U_TD_U_EXTRA_CUSTOM]  = custom_extra_td;
}

socd_cleaner_t socd_opposing_pairs[] = {
  {{KC_F, KC_S}, SOCD_CLEANER_LAST},
  {{KC_R, KC_T}, SOCD_CLEANER_LAST},
};
