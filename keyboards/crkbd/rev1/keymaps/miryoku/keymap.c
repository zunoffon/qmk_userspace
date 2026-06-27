// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

// 1/4 - Include header for Miryoku constants (e.g., U_EXTRA, U_BASE)
#include "manna-harbour_miryoku.h"

// 2/4 - Define custom Tap Dance behavior
void u_td_fn_U_EXTRA_custom(tap_dance_state_t *state, void *user_data) {
  uprintf("%s: Triggered! count: [%d]\n", __func__, state->count);
  if (state->count == 2) { // Default behavior
    uprintf("%s: Setting Miryoku EXTRA layer\n", __func__);
    default_layer_set((layer_state_t)1 << U_EXTRA);
  }
}

// 3/4 - Declare external reference to the core Miryoku tap_dance_actions array
extern tap_dance_action_t tap_dance_actions[];

void keyboard_post_init_user(void) {
  // 4/4 - Hook into post_init to perform the runtime override
  // Create our custom action struct
  tap_dance_action_t custom_extra_td = ACTION_TAP_DANCE_FN(u_td_fn_U_EXTRA_custom);

  // Patch the Miryoku action table.
  // We target index 2 because:
  // enum { U_TD_BOOT, U_TD_BASE, U_TD_EXTRA, ... }; // U_TD_EXTRA corresponds to index 2
  // Referenced from: users\miryoku\manna-harbour_miryoku.c, users/miryoku/miryoku_babel/miryoku_layer_list.h
#define U_TD_U_EXTRA_ENUM_INDEX 2
  tap_dance_actions[U_TD_U_EXTRA_ENUM_INDEX] = custom_extra_td;
}

socd_cleaner_t socd_opposing_pairs[] = {
  {{KC_F, KC_S}, SOCD_CLEANER_LAST},
  {{KC_R, KC_T}, SOCD_CLEANER_LAST},
};
